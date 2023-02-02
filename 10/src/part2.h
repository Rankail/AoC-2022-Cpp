#pragma once

#include <fstream>

class Part2 {
public:
    Part2() {}
    
    void run(std::ifstream& file);
    void draw();
    void printResult();

private:
    bool board[240];
    int regx;
    int cycle;
    int sum;
};