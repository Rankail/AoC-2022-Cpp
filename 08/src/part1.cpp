#include "part1.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

static bool allShorter(const std::vector<std::vector<int>>& grid, int x, int y) {
    int h = grid[x][y];
    bool no = false;
    for (int i = x - 1; i >= 0; i--) {
        if (grid[i][y] >= h) {
            no = true;
            break;
        }
    }
    if (!no) return true;
    no = false;
    for (int i = x + 1; i < grid.size(); i++) {
        if (grid[i][y] >= h) {
            no = true;
            break;
        }
    }
    if (!no) return true;
    no = false;
    for (int i = y - 1; i >= 0; i--) {
        if (grid[x][i] >= h) {
            no = true;
            break;
        }
    }
    if (!no) return true;
    no = false;
    for (int i = y + 1; i < grid[x].size(); i++) {
        if (grid[x][i] >= h) {
            no = true;
            break;
        }
    }
    return !no;
}

void Part1::run(std::ifstream& file) {
    std::string line;
    std::vector<std::vector<int>> grid;
    int i = 0;
    while (std::getline(file, line)) {
        grid.push_back(std::vector<int>());
        for (char c : line) {
            grid[i].push_back((int)(c - '0'));
        }
        i++;
    }
    int count = grid.size() * 2 + grid[0].size() * 2 - 4;
    for (int i = 1; i < grid.size() - 1; i++) {
        for (int j = 1; j < grid[i].size() - 1; j++) {
            if (allShorter(grid, i, j)) {
                count++;
            }
        }
    }

    result = count;
}

void Part1::printResult() {
    std::cout << "Result: " << result << std::endl;
}