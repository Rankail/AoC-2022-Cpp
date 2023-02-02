#include "part2.h"

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

static struct Dir {
    std::shared_ptr<Dir> parent;
    std::unordered_map<std::string, std::shared_ptr<Dir>> dirs = std::unordered_map<std::string, std::shared_ptr<Dir>>();
    unsigned size = 0;

    Dir(std::shared_ptr<Dir> parent) : parent(parent) {}
};

static std::shared_ptr<Dir> getTreeFromLines(std::ifstream& file) {
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

static unsigned getSize(std::shared_ptr<Dir> dir) {
    for (auto& d : dir->dirs) {
        dir->size += getSize(d.second);
    }
    return dir->size;
}

static void getMinOverTarget(unsigned& m, const unsigned target, std::shared_ptr<Dir> dir) {
    if (dir->size < target) return;

    m = std::min(m, dir->size);
    for (auto& d : dir->dirs) {
        getMinOverTarget(m, target, d.second);
    }
}

void Part2::run(std::ifstream& file) {
    auto root = getTreeFromLines(file);
    getSize(root);

    auto to_free = root->size - 40000000;
    unsigned m = root->size;
    getMinOverTarget(m, to_free, root);

    result = m;
}

void Part2::printResult() {
    std::cout << "Result: " << result << std::endl;
}