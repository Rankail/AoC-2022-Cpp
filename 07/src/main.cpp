#include <fstream>
#include <iostream>
#include <chrono>
#include <string>
#include <memory>
#include <unordered_map>

#ifdef TIMEIT
#define DOUT(x)
#else
#define DOUT(x) x
#endif

typedef unsigned ResultType;

struct Dir {
    std::shared_ptr<Dir> parent;
    std::unordered_map<std::string, std::shared_ptr<Dir>> dirs = std::unordered_map<std::string, std::shared_ptr<Dir>>();
    unsigned size = 0;

    Dir(std::shared_ptr<Dir> parent) : parent(parent) {}
};

std::shared_ptr<Dir> getTreeFromLines(std::ifstream& file) {
    std::string line;
    std::getline(file, line);
    auto root = std::make_shared<Dir>(nullptr);
    auto cwd = root;
    while (std::getline(file, line)) {
        if (line == "$ ls") {
            while (std::getline(file, line) && line.substr(0, 4) != "$ cd") {
                if (line[0] == 'd') {
                    cwd->dirs.emplace(line.substr(4), std::make_shared<Dir>(cwd));
                }
                else {
                    cwd->size += atoi(line.substr(0, line.find(' ')).c_str());
                }
            }
        }
        if (line == "$ cd ..") {
            cwd = cwd->parent;
        }
        else if (line.substr(0, 4) == "$ cd") {
            cwd = cwd->dirs[line.substr(5)];
        }
    }
    return root;
}

void printTreeSub(std::shared_ptr<Dir> dir, int depth = 0) {
    std::string off = "";
    for (int i = 0; i <= depth; i++) {
        off += '\t';
    }
    for (auto& d : dir->dirs) {
        std::cout << off << d.first << " " << d.second->size << std::endl;
        printTreeSub(d.second, depth + 1);
    }
}

void printTree(std::shared_ptr<Dir> root) {
    std::cout << "/ " << root->size << std::endl;
    printTreeSub(root);
}

ResultType getSize(std::shared_ptr<Dir> dir) {
    for (auto& d : dir->dirs) {
        dir->size += getSize(d.second);
    }
    return dir->size;
}

#ifdef PART1
void getSumDirsMax100k(unsigned& sum, std::shared_ptr<Dir> dir) {
    if (dir->size < 100000) {
        sum += dir->size;
    }

    for (auto& d : dir->dirs) {
        getSumDirsMax100k(sum, d.second);
    }
}

ResultType solve(std::ifstream& file) {
    auto root = getTreeFromLines(file);
    getSize(root);
    
    DOUT(printTree(root));
    unsigned sum = 0;
    getSumDirsMax100k(sum, root);
    return sum;
}
#else
void getMinOverTarget(unsigned& m, const unsigned target, std::shared_ptr<Dir> dir) {
    if (dir->size < target) return;

    m = std::min(m, dir->size);
    for (auto& d : dir->dirs) {
        getMinOverTarget(m, target, d.second);
    }
}

ResultType solve(std::ifstream& file) {
    auto root = getTreeFromLines(file);
    getSize(root);

    auto to_free = root->size - 40000000;
    unsigned m = root->size;
    getMinOverTarget(m, to_free, root);
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