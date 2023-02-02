#include "part2.h"

#include <iostream>
#include <fstream>
#include <string>

void Part2::run(std::ifstream& file) {
    std::string line;
    int score = 0;
    while (std::getline(file, line)) {
        int opp = int(line[0] - 'A');
        uint8_t me = int(line[2] - 'X');
        score += me * 3;
        score += (opp + me - 1 + 3) % 3 + 1;
    }
    result = score;
}

void Part2::printResult() {
    std::cout << "Result: " << result << std::endl;
}