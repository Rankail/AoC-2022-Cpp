#include "part2.h"

#include <iostream>
#include <fstream>
#include <string>

void Part2::run(std::ifstream& file) {
    std::string line;
    std::getline(file, line);
    int i = 0;

    constexpr int WINDOW = 14;

    while (i < line.length() - WINDOW) {
    outer:
        for (int j = 0; j < WINDOW - 1; j++) {
            for (int k = j + 1; k < WINDOW; k++) {
                if (line[i + j] == line[i + k]) {
                    i += j + 1;
                    goto outer;
                }
            }
        }
        break;
    }

    result = i + WINDOW;
}

void Part2::printResult() {
    std::cout << "Result: " << result << std::endl;
}