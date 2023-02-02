#pragma once

#include <fstream>

class Part2 {
public:
	Part2() {}
	bool* run(std::ifstream& file);
	void draw();

private:
	bool board[240];
	int regx;
	int cycle;
	int sum;
};