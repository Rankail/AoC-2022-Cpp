#pragma once

#include <fstream>

class Part1 {
public:
	Part1() {}
	int run(std::ifstream& file);
	void endCycle();

private:
	int regx;
	int cycle;
	int sum;
};