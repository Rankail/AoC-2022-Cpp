#include "part2.h"

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

struct Point {
    int x;
    int y;

    bool operator==(const Point& other) const {
        return this->x == other.x && this->y == other.y;
    }

    struct HashFunction
    {
        size_t operator()(const Point& p) const
        {
            return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
        }
    };
};

static void move(const Point& head, Point& tail) {
    if (std::abs(head.x - tail.x) < 2 && std::abs(head.y - tail.y) < 2) return;
    if (head.x < tail.x) {
        tail.x--;
    }
    if (head.x > tail.x) {
        tail.x++;
    }
    if (head.y < tail.y) {
        tail.y--;
    }
    if (head.y > tail.y) {
        tail.y++;
    }
}

void Part2::run(std::ifstream& file) {
    std::vector<Point> nodes = std::vector<Point>();
    for (int i = 0; i < 10; i++) {
        nodes.push_back(Point{ 0, 0 });
    }

    auto visited = std::unordered_set<Point, Point::HashFunction>();

    std::string line;
    while (std::getline(file, line)) {
        int dx = 0;
        int dy = 0;
        if (line[0] == 'R') dx = 1;
        else if (line[0] == 'L') dx = -1;
        else if (line[0] == 'U') dy = 1;
        else if (line[0] == 'D') dy = -1;

        for (int i = 0; i < atoi(line.substr(2).c_str()); i++) {
            nodes[0].x += dx;
            nodes[0].y += dy;
            for (int i = 0; i < 9; i++) {
                move(nodes[i], nodes[i + 1]);
            }
            visited.insert(nodes[9]);
        }
    }

    result = visited.size();
}

void Part2::printResult() {
    std::cout << "Result: " << result << std::endl;
}