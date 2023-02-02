#include "part2.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

static int shorterCount(const std::vector<std::vector<int>>& grid, int x, int y) {
    int h = grid[x][y];
    int score = 1;
    int c = 0;
    bool no = false;
    for (int i = x - 1; i >= 0; i--) {
        c++;
        if (grid[i][y] >= h) break;
    }
    score *= c;
    c = 0;
    for (int i = x + 1; i < grid.size(); i++) {
        c++;
        if (grid[i][y] >= h) break;
    }
    score *= c;
    c = 0;
    for (int i = y - 1; i >= 0; i--) {
        c++;
        if (grid[x][i] >= h) break;
    }
    score *= c;
    c = 0;
    for (int i = y + 1; i < grid[x].size(); i++) {
        c++;
        if (grid[x][i] >= h) break;
    }
    return score *= c;
}

void Part2::run(std::ifstream& file) {
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
    int m = 0;
    for (int i = 1; i < grid.size() - 1; i++) {
        for (int j = 1; j < grid[i].size() - 1; j++) {
            m = std::max(m, shorterCount(grid, i, j));
        }
    }

    result = m;
}

void Part2::printResult() {
    std::cout << "Result: " << result << std::endl;
}