#include "part1.h"

#include <iostream>
#include <fstream>
#include <string>

void Part1::run(std::ifstream& file) {
    std::string line;
    int score = 0;
    while (std::getline(file, line)) {
        int opp = int(line[0] - 'A');
        uint8_t me = int(line[2] - 'X');
        score += me + 1;
        score += (me + 3 - opp + 1) % 3 * 3;
    }
    result = score;
}

void Part1::printResult() {
    std::cout << "Result: " << result << std::endl;
}