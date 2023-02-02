#pragma once

#include <fstream>

class Part2 {
public:
    Part2() {}
    
    void run(std::ifstream& file);
    void printResult();

private:
    std::string result;
};