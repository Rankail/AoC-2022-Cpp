#include <fstream>
#include <iostream>
#include <chrono>
#include <string>

#include "Part1.h"
#include "part2.h"

#ifdef TIMEIT
#define DOUT(x)
#else
#define DOUT(x) x
#endif

typedef int ResultType;

#ifdef PART1
ResultType solve(std::ifstream& file) {
    Part1 part = Part1();
    return part.run(file);
}
#else
bool* solve(std::ifstream& file) {
    Part2 part = Part2();
    return part.run(file);
}
#endif

#ifndef TIMEIT

int main(int argc, char** argv) {
#ifdef TEST
    std::ifstream file("./src/test.txt");
#else
    std::ifstream file("./src/input.txt");
#endif

    if (!file.is_open()) {
        throw std::ios::failure("Failed to read file\n");
    }

    auto startTime = std::chrono::high_resolution_clock::now();

    auto result = solve(file);

    auto endTime = std::chrono::high_resolution_clock::now();

    file.close();

    std::cout << "Result: " << result << "\nFinished after "
        << std::chrono::duration<double, std::milli>(endTime - startTime).count()/1000. << "ms\n";

    return 0;
}

#else
int main(int argc, char** argv) {
    #define ITERATIONS 1000.
    auto startTime = std::chrono::high_resolution_clock::now();
    bool* result;
    for (int i = 0; i < ITERATIONS; i++) {
#ifdef TEST
        std::ifstream file("./src/test.txt");
#else
        std::ifstream file("./src/input.txt");
#endif

        if (!file.is_open()) {
            throw std::ios::failure("Failed to read file\n");
        }
    
        result = solve(file);
        file.close();
    }
    auto endTime = std::chrono::high_resolution_clock::now();

    std::cout << "Result:";
    for (int i = 0; i < 240; i++) {
        if (i % 40 == 0) std::cout << "\n";
        std::cout << (result[i] ? '#' : '.');
    }

    std::cout  << "\nFinished " << (int)ITERATIONS << " iterations after "
        << std::chrono::duration<double>(endTime - startTime).count() << " s with an average of "
        << std::chrono::duration<double, std::milli>(endTime - startTime).count() / ITERATIONS << " ms\n";

    return 0;
}
#endif