#include "part2.h"

#include <iostream>
#include <fstream>
#include <string>

void Part2::run(std::ifstream& file) {
    for (int i = 0; i < 240; i++) {
        board[i] = false;
    }
    regx = 1;
    cycle = 0;
    sum = 0;
    std::string line;
    while (std::getline(file, line) && cycle < 240) {
        if (line == "noop") {
            draw();
            cycle++;
            continue;
        }

        int num = atoi(line.substr(5).c_str());
        draw();
        cycle++;
        if (cycle >= 240) break;
        draw();
        cycle++;
        regx += num;

    }
}

void Part2::draw() {
    if (std::abs(regx - (cycle % 40)) < 2) {
        board[cycle] = true;
    }
}

void Part2::printResult() {
    std::cout << "Result:";
    for (int i = 0; i < 240; i++) {
        if (i % 40 == 0) std::cout << std::endl;
        std::cout << (board[i] ? '#' : ' ');
    }
    std::cout << std::endl;;
}