#include "part2.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void Part2::run(std::ifstream& file) {
    std::string line;
    int sum = 0;
    std::vector<std::string> lines = std::vector<std::string>();
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    for (int i = 0; i < lines.size(); i += 3) {
        for (int j = 0; j < lines[i].size(); j++) {
            char c = lines[i][j];
            if (lines[i + 1].find(c) != std::string::npos && lines[i + 2].find(c) != std::string::npos) {
                if (c - 'a' < 0) {
                    sum += c - 'A' + 27;
                }
                else {
                    sum += c - 'a' + 1;
                }
                break;
            }
        }
    }

    result = sum;
}

void Part2::printResult() {
    std::cout << "Result: " << result << std::endl;
}