#include "part1.h"

#include <iostream>
#include <fstream>
#include <string>

void Part1::run(std::ifstream& file) {
    std::string line;
    int count = 0;
    while (std::getline(file, line)) {
        int s1 = line.find("-");
        int s2 = line.find(",", s1);
        int s3 = line.find("-", s2);
        int a = atoi(line.substr(0, s1).c_str());
        int b = atoi(line.substr(s1 + 1, s2).c_str());
        int c = atoi(line.substr(s2 + 1, s3).c_str());
        int d = atoi(line.substr(s3 + 1).c_str());

        if ((a - c) * (b - d) <= 0) {
            count++;
        }
    }

    result = count;
}

void Part1::printResult() {
    std::cout << "Result: " << result << std::endl;
}