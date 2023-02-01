#include <fstream>
#include <iostream>
#include <chrono>
#include <string>
#include <vector>

#ifdef PART1
std::string solve(std::ifstream& file) {
    std::string line;
    std::getline(file, line);
    std::vector<std::vector<char>> stacks = std::vector<std::vector<char>>((line.length() + 3) / 4);
    do {
        for (int i = 1; i < line.length(); i += 4) {
            if (line[i] == ' ') continue;
            stacks[i / 4].insert(stacks[i / 4].begin(), line[i]);
        }
    } while (std::getline(file, line) && line.substr(0, 2) != " 1");

    std::getline(file, line);
    while (std::getline(file, line)) {
        int i1 = line.find(' ', line.find(' ') + 1);
        int count = atoi(line.substr(5, i1 - 5).c_str());
        int from = atoi(line.substr(i1 + 6, 1).c_str()) - 1;
        int to = atoi(line.substr(i1 + 11, 1).c_str()) - 1;
        for (int i = 0; i < count; i++) {
            stacks[to].push_back(stacks[from].back());
            stacks[from].pop_back();
        }
    }

    std::string result = "";
    for (auto& stack : stacks) {
        result += stack.back();
    }

    return result;
}
#else
std::string solve(std::ifstream& file) {
    std::string line;
    std::getline(file, line);
    std::vector<std::vector<char>> stacks = std::vector<std::vector<char>>((line.length() + 3) / 4);
    do {
        for (int i = 1; i < line.length(); i += 4) {
            if (line[i] == ' ') continue;
            stacks[i / 4].insert(stacks[i / 4].begin(), line[i]);
        }
    } while (std::getline(file, line) && line.substr(0, 2) != " 1");


    std::getline(file, line);
    while (std::getline(file, line)) {
        int i1 = line.find(' ', line.find(' ') + 1);
        int count = atoi(line.substr(5, i1 - 5).c_str());
        int from = atoi(line.substr(i1 + 6, 1).c_str()) - 1;
        int to = atoi(line.substr(i1 + 11, 1).c_str()) - 1;
        int fromStart = stacks[from].size() - count;
        for (int i = 0; i < count; i++) {
            stacks[to].push_back(stacks[from][fromStart + i]);
        }
        stacks[from].erase(stacks[from].end() - count, stacks[from].end());
    }

    std::string result = "";
    for (auto& stack : stacks) {
        result += stack.back();
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
    std::string result;
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