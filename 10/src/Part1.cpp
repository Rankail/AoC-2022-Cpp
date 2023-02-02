#include "part1.h"

#include <iostream>
#include <fstream>
#include <string>

void Part1::run(std::ifstream& file) {
    regx = 1;
    cycle = 0;
    sum = 0;
    std::string line;
    while (std::getline(file, line) && cycle < 221) {
        if (line == "noop") {
            cycle++;
            endCycle();
            continue;
        }

        int num = atoi(line.substr(5).c_str());
        cycle++;
        endCycle();
        cycle++;
        endCycle();
        regx += num;
    }

    result = sum;
}

void Part1::endCycle() {
    if ((cycle + 20) % 40 == 0) {
        sum += cycle * regx;
    }
}

void Part1::printResult() {
    std::cout << "Result: " << result << std::endl;
}