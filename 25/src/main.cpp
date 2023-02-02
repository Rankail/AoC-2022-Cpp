#ifdef PART1
#include "part1.h"
#else
#include "part2.h"
#endif

#include <chrono>
#include <iostream>

int main(int argc, char** argv) {
#ifdef TEST
    std::ifstream file("./src/example.txt");
#else
    std::ifstream file("./src/input.txt");
#endif

    #ifdef PART1
    Part1 part = Part1();
    #else
    Part2 part = Part2();
    #endif

    if (!file.is_open()) {
        throw std::ios::failure("Failed to read file\n");
    }

    auto startTime = std::chrono::high_resolution_clock::now();

    part.run(file);

    auto endTime = std::chrono::high_resolution_clock::now();

    file.close();

    part.printResult();
    std::cout << "Finished after "
        << std::chrono::duration<double, std::milli>(endTime - startTime).count() << "ms\n";

    return 0;
}