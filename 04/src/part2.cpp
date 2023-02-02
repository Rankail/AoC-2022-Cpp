#include "part2.h"

#include <iostream>
#include <fstream>
#include <string>

void Part2::run(std::ifstream& file) {
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

        if ((a <= c && c <= b) || (a <= d && d <= b) || (c <= a && a <= d) || (c <= b && b <= d)) {
            count++;
        }
    }

    result = count;
}

void Part2::printResult() {
    std::cout << "Result: " << result << std::endl;
}