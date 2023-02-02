#include "part1.h"

#include <iostream>
#include <fstream>
#include <string>

void Part1::run(std::ifstream& file) {
    std::string line;
    int sum = 0;

    while (std::getline(file, line)) {
        const int half = line.length() / 2;
        for (int i = 0; i < half; i++) {
            if (line.find(line[i], half) != std::string::npos) {
                if (line[i] - 'a' < 0) {
                    sum += line[i] - 'A' + 27;
                }
                else {
                    sum += line[i] - 'a' + 1;
                }
                break;
            }
        }
    }
    result = sum;
}

void Part1::printResult() {
    std::cout << "Result: " << result << std::endl;
}