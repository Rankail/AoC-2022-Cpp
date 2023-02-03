#pragma once

#include <fstream>

class Part1 {
public:
    Part1() {}
    
    void run(std::ifstream& file);
    void printResult();

private:
    uint64_t result;
};