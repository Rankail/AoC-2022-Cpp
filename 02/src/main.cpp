#include <fstream>
#include <iostream>
#include <chrono>
#include <string>

#ifdef PART1
int solve(std::ifstream& file) {
    std::string line;
    int score = 0;
    while (std::getline(file, line)) {
        int opp = int(line[0] - 'A');
        uint8_t me = int(line[2] - 'X');
        score += me + 1;
        score += (me + 3 - opp + 1) % 3 * 3;
    }
    return score;
}
#else
int solve(std::ifstream& file) {
    std::string line;
    int score = 0;
    while (std::getline(file, line)) {
        int opp = int(line[0] - 'A');
        uint8_t me = int(line[2] - 'X');
        score += me * 3;
        score += (opp + me - 1 + 3) % 3 + 1;
    }
    return score;
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