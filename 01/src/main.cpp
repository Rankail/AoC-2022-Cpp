#include <fstream>
#include <iostream>
#include <chrono>
#include <string>
#include <filesystem>

#ifdef PART1
int solve(std::ifstream& file) {
    std::string line;
    int m = 0;
    int p = 0;
    while (std::getline(file, line)) {
        if (line == "") {
            m = std::max(m, p);
            p = 0;
        } else {
            p += atoi(line.c_str());
        }
    }

    return m;
}
#else
int solve(std::ifstream& file) {
    int maxs[3] = {0};
    std::string line;
    int p = 0;
    while (std::getline(file, line)) {
        if (line == "") {
            if (p < maxs[0]) {
                p = 0;
                continue;
            }
            if (p > maxs[2]) {
                maxs[0] = maxs[1];
                maxs[1] = maxs[2];
                maxs[2] = p;
            } else if (p > maxs[1]) {
                maxs[0] = maxs[1];
                maxs[1] = p;
            } else if (p > maxs[0]) {
                maxs[0] = p;
            }
            p = 0;
        } else {
            p += atoi(line.c_str());
        }
    }
    return maxs[0] + maxs[1] + maxs[2];
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
    int result;
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

    std::cout << "Result: " << result << "\nFinished " << (int)ITERATIONS << " iterations after "
        << std::chrono::duration<double>(endTime - startTime).count() << " s with an average of "
        << std::chrono::duration<double, std::milli>(endTime - startTime).count() / ITERATIONS << " ms\n";

    return 0;
}
#endif