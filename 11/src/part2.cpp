#include "part2.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Monkey {
    char op;
    int operand;
    int tTarget;
    int fTarget;
    int test;
    int count = 0;
    std::vector<uint64_t> items;
};

void Part2::run(std::ifstream& file) {
    std::vector<Monkey> monkeys = std::vector<Monkey>();

    std::string line;
    while (std::getline(file, line)) {
        std::getline(file, line);

        Monkey m = Monkey();

        m.items = std::vector< uint64_t>();
        int prevC = 0;
        int nextC = 0;
        line = line.substr(18);
        while ((nextC = line.find(',', prevC)) != std::string::npos) {
            m.items.push_back(std::stoi(line.substr(prevC, nextC - prevC)));
            prevC = nextC + 1;
        }
        m.items.push_back(std::stoi(line.substr(prevC)));

        std::getline(file, line);
        m.op = line[23];
        m.operand = (line[25] == 'o') ? -1 : std::stoi(line.substr(25));

        std::getline(file, line);
        m.test = std::stoi(line.substr(21));

        std::getline(file, line);
        m.tTarget = std::stoi(line.substr(29));
        std::getline(file, line);
        m.fTarget = std::stoi(line.substr(30));

        std::getline(file, line);

        monkeys.emplace_back(m);
    }

    int div = 1;
    for (auto& m : monkeys) div *= m.test;

    for (int n = 0; n < 10000; n++) {
        for (int i = 0; i < monkeys.size(); i++) {
            auto& m = monkeys[i];
            for (int j = 0; j < m.items.size(); j++) {
                if (m.op == '+') {
                    if (m.operand == -1) {
                        m.items[j] *= 2;
                    }
                    else {
                        m.items[j] += m.operand;
                    }
                }
                else {
                    if (m.operand == -1) {
                        m.items[j] *= m.items[j];
                    }
                    else {
                        m.items[j] *= m.operand;
                    }
                }

                m.count++;
                m.items[j] %= div;
                if (m.items[j] % m.test == 0) {
                    monkeys[m.tTarget].items.push_back(m.items[j]);
                }
                else {
                    monkeys[m.fTarget].items.push_back(m.items[j]);
                }
            }
            m.items.clear();
        }
    }

    uint64_t m1 = 0, m2 = 0;
    for (auto& m : monkeys) {
        if (m.count > m1) {
            m2 = m1;
            m1 = m.count;
        }
        else if (m.count > m2) {
            m2 = m.count;
        }
    }
    result = m1 * m2;
}

void Part2::printResult() {
    std::cout << "Result: " << result << std::endl;
}