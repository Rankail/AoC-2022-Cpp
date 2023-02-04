#pragma once

#include <fstream>
#include <vector>

struct Pos {
    int x, y;

    const bool operator==(const Pos& other) const {
        return this->x == other.x && this->y == other.y;
    }

    const bool operator!=(const Pos& other) const {
        return !(*this == other);
    }

    struct HashFunction {
        size_t operator()(const Pos& p) const {
            return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y));
        }
    };
};

class Part2 {
public:
    Part2() {}
    
    void run(std::ifstream& file);
    void printResult();

    char elevation(Pos p);

private:
    int result;

    Pos end;
    std::vector<std::string> grid;
};