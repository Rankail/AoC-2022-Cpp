#include <fstream>
#include <iostream>
#include <chrono>
#include <string>
#include <vector>

#ifdef PART1
int solve(std::ifstream& file) {
    std::string line;
    int result = 0;

    while (std::getline(file, line)) {
        const int half = line.length() / 2;
        for (int i = 0; i < half; i++) {
            if (line.find(line[i], half) != std::string::npos) {
                if (line[i] - 'a' < 0) {
                    result += line[i] - 'A' + 27;
                } else {
                    result += line[i] - 'a' + 1;
                }
                break;
            }
        }
    }
    return result;
}
#else
int solve(std::ifstream& file) {
    std::string line;
    int result = 0;
    std::vector<std::string> lines = std::vector<std::string>();
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    for (int i = 0; i < lines.size(); i += 3) {
        for (int j = 0; j < lines[i].size(); j++) {
            char c = lines[i][j];
            if (lines[i + 1].find(c) != std::string::npos && lines[i + 2].find(c) != std::string::npos) {
                if (c - 'a' < 0) {
                    result += c - 'A' + 27;
                } else {
                    result += c - 'a' + 1;
                }
                break;
            }
        }
    }

    return result;
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