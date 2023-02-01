#include <fstream>
#include <iostream>
#include <chrono>
#include <string>
#include <memory>
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

#ifdef TIMEIT
#define DOUT(x)
#else
#define DOUT(x) x
#endif

typedef int ResultType;

void move(const Point& head, Point& tail) {
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

#ifdef PART1
ResultType solve(std::ifstream& file) {
    std::vector<Point> nodes = std::vector<Point>();
    for (int i = 0; i < 10; i++) {
        nodes.push_back(Point{ 0, 0 });
    }
    auto tail = Point{ 0,0 };
    auto head = Point{ 0,0 };
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
            head.x += dx;
            head.y += dy;
            move(head, tail);
            visited.insert(tail);
            DOUT(std::cout << tail.x << " " << tail.y << std::endl);
        }
       
    }

    DOUT(
    std::cout << "\n";
    for (auto& p : visited) {
        std::cout << p.x << " " << p.y << std::endl;
    })

    return visited.size();
}
#else
ResultType solve(std::ifstream& file) {
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
                move(nodes[i], nodes[i+1]);
            }
            visited.insert(nodes[9]);
        }
    }

    return visited.size();
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