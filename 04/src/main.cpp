#include <fstream>
#include <iostream>
#include <chrono>
#include <string>

#ifdef PART1
int solve(std::ifstream& file) {
    std::string line;
    int count = 0;
    while (std::getline(file, line)) {
        int s1 = line.find("-");
        int s2 = line.find(",", s1);
        int s3 = line.find("-", s2);
        int a = atoi(line.substr(0, s1).c_str());
        int b = atoi(line.substr(s1 + 1, s2).c_str());
        int c = atoi(line.substr(s2 + 1, s3).c_str());
        int d = atoi(line.substr(s3 + 1).c_str());

        if ((a - c) * (b - d) <= 0) {
            count++;
        }
    }

    return count;
}
#else
int solve(std::ifstream& file) {
    std::string line;
    int count = 0;
    while (std::getline(file, line)) {
        int s1 = line.find("-");
        int s2 = line.find(",", s1);
        int s3 = line.find("-", s2);
        int a = atoi(line.substr(0, s1).c_str());
        int b = atoi(line.substr(s1 + 1, s2).c_str());
        int c = atoi(line.substr(s2 + 1, s3).c_str());
        int d = atoi(line.substr(s3 + 1).c_str());

        if ((a <= c && c <= b) || (a <= d && d <= b) || (c <= a && a <= d) || (c <= b && b <= d)) {
            count++;
        }
    }

    return count;
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