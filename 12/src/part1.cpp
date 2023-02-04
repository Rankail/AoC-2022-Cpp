#include "part1.h"

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <deque>

struct Node {
	Pos pos;
	int cost;
	char height;
};

char Part1::elevation(Pos p) {
	char c = grid[p.x][p.y];
	if (c == 'S') return 'a';
	if (c == 'E') return 'z';
	return c;
}

void Part1::run(std::ifstream& file) {
	grid = std::vector<std::string>();
	std::string line;
	Pos startPos;
	int row = 0;
	while (std::getline(file, line)) {
		int idx = line.find('S');
		if (idx != std::string::npos) startPos = Pos{ row, idx };
		idx = line.find('E');
		if (idx != std::string::npos) end = Pos{ row, idx };
		
		grid.push_back(line);
		row++;
	}

	int ds[4][2] = { {0,1},{1,0},{0,-1},{-1,0} };

	std::deque<Node> nodes = std::deque<Node>();
	auto visited = std::unordered_set<Pos, Pos::HashFunction>();
	Node start = Node{ startPos, 0, elevation(startPos) };
	nodes.push_back(start);
	visited.insert(startPos);
	char m = '0';
	while (!nodes.empty()) {
		auto cur = nodes.front();
		nodes.pop_front();
		m = std::max(m, elevation(cur.pos));
		if (cur.pos == end) {
			result = cur.cost;
			return;
		}
		
		for (auto d : ds) {
			Pos test = Pos{ cur.pos.x + d[0], cur.pos.y + d[1] };

			if (test.x < 0 || test.y < 0 || test.x >= grid.size() || test.y >= grid[0].length()) continue;
			if (elevation(test) > cur.height + 1) continue;
			auto it = visited.find(test);
			if (it != visited.end()) continue;

			visited.insert(test);
			nodes.push_back(Node{ test, cur.cost + 1, elevation(test) });
		}
	}
	std::cout << "Error\n";
}

void Part1::printResult() {
    std::cout << "Result: " << result << std::endl;
}