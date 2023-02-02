#include "part2.h"

#include <iostream>
#include <fstream>
#include <string>

void Part2::run(std::ifstream& file) {
    int maxs[3] = { 0 };
    std::string line;
    int p = 0;
    while (std::getline(file, line)) {
        if (line == "") {
            if (p < maxs[0]) {
                p = 0;
                continue;
            }
            if (p > maxs[2]) {
                maxs[0] = maxs[1];
                maxs[1] = maxs[2];
                maxs[2] = p;
            }
            else if (p > maxs[1]) {
                maxs[0] = maxs[1];
                maxs[1] = p;
            }
            else if (p > maxs[0]) {
                maxs[0] = p;
            }
            p = 0;
        }
        else {
            p += atoi(line.c_str());
        }
    }
    result = maxs[0] + maxs[1] + maxs[2];
}

void Part2::printResult() {
    std::cout << "Result: " << result << std::endl;
}