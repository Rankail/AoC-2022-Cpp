#include <fstream>
#include <iostream>
#include <chrono>
#include <string>
#include <vector>

#ifdef TIMEIT
#define DOUT(x)
#else
#define DOUT(x) x
#endif

typedef int ResultType;

void printArr(std::vector<std::vector<bool>> marks) {
    for (int i = 0; i < marks.size(); i++) {
        for (int j = 0; j < marks[i].size(); j++) {
            std::cout << marks[i][j];
        }
        std::cout << std::endl;
    }
}

#ifdef PART1
bool allShorter(const std::vector<std::vector<int>>& grid, int x, int y) {
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

ResultType solve(std::ifstream& file) {
    std::string line;
    std::vector<std::vector<int>> grid;
    int i = 0;
    while (std::getline(file, line)) {
        grid.push_back(std::vector<int>());
        for (char c : line) {
            grid[i].push_back((int)(c-'0'));
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

    return count;
}
#else
int shorterCount(const std::vector<std::vector<int>>& grid, int x, int y) {
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

ResultType solve(std::ifstream& file) {
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
    return m;
}
#endif

#ifndef TIMEIT

int main(int argc, char** argv) {
#ifdef TEST
    std::ifstream file("./src/test.txt");
#else
    std::ifstream file("./src/input.txt");
#endif

    if (!file.is_open()) {
        throw std::ios::failure("Failed to read file\n");
    }

    auto startTime = std::chrono::high_resolution_clock::now();

    auto result = solve(file);

    auto endTime = std::chrono::high_resolution_clock::now();

    file.close();

    std::cout << "Result: " << result << "\nFinished after "
        << std::chrono::duration<double, std::milli>(endTime - startTime).count()/1000. << "ms\n";

    return 0;
}

#else
int main(int argc, char** argv) {
    #define ITERATIONS 1000.
    auto startTime = std::chrono::high_resolution_clock::now();
    ResultType result;
    for (int i = 0; i < ITERATIONS; i++) {
#ifdef TEST
        std::ifstream file("./src/test.txt");
#else
        std::ifstream file("./src/input.txt");
#endif

        if (!file.is_open()) {
            throw std::ios::failure("Failed to read file\n");
        }
    
        result = solve(file);
        file.close();
    }
    auto endTime = std::chrono::high_resolution_clock::now();

    std::cout << "Result: " << result << "\nFinished " << (int)ITERATIONS << " iterations after "
        << std::chrono::duration<double>(endTime - startTime).count() << " s with an average of "
        << std::chrono::duration<double, std::milli>(endTime - startTime).count() / ITERATIONS << " ms\n";

    return 0;
}
#endif