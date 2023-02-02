#include "part2.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void Part2::run(std::ifstream& file) {
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

    std::string tops = "";
    for (auto& stack : stacks) {
        tops += stack.back();
    }

    result = tops;
}

void Part2::printResult() {
    std::cout << "Result: " << result << std::endl;
}