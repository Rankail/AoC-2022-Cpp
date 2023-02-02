#pragma once

#include <fstream>

class Part1 {
public:
    Part1() {}
    
    void run(std::ifstream& file);
    void printResult();

    void endCycle();

private:
    int result;

    int regx;
    int cycle;
    int sum;
};