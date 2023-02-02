#include "part1.h"

#include <iostream>
#include <fstream>
#include <string>

void Part1::run(std::ifstream& file) {
    std::string line;
    int m = 0;
    int p = 0;
    while (std::getline(file, line)) {
        if (line == "") {
            m = std::max(m, p);
            p = 0;
        }
        else {
            p += atoi(line.c_str());
        }
    }

    result = m;
}

void Part1::printResult() {
    std::cout << "Result: " << result << std::endl;
}