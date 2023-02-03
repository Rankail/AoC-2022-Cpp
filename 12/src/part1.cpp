#include "part1.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>

struct Node {
	Pos pos;
	int cost;
	int dist;
	char height;
};

int Part1::dist(Pos p) {
	return std::abs(end.x - p.x) + std::abs(end.y - p.y);
}

char Part1::elevation(Pos p) {
	char c = grid[p.x][p.y];
	if (c == 'S') return 'a';
	if (c == 'E') return 'z';
	return c;
}

static int cost(const Node& a) {
	return a.cost + a.dist - a.height;
}

static int costLess(const Node& a, const Node& b) {
	return cost(a) < cost(b);
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

	std::priority_queue<Node, std::vector<Node>, costLess> q;
	std::vector<Node> nodes = std::vector<Node>();
	auto visited = std::unordered_set<Pos, Pos::HashFunction>();
	Node start = Node{ startPos, 0, dist(startPos), elevation(startPos) };
	nodes.push_back(start);
	visited[startPos] = start;
	char m = '0';
	while (!nodes.empty()) {
		auto curIt = std::min_element(nodes.begin(), nodes.end(), [](const Node& a, const Node& b) { return cost(a) < cost(b); });
		auto cur = *curIt;
		m = std::max(m, elevation(cur.pos));
		if (cur.pos == end) {
			result = cur.cost;
			return;
		}
		nodes.erase(curIt);

		
		for (auto d : ds) {
			Pos test = Pos{ cur.pos.x + d[0], cur.pos.y + d[1] };

			if (test.x < 0 || test.y < 0 || test.x >= grid.size() || test.y >= grid[0].length()) continue;
			if (elevation(test) > cur.height + 1) continue;
			auto it = visited.find(test);
			if (it != visited.end()) continue;

			visited.insert(test);
			nodes.push_back(Node{ test, cur.cost + 1, dist(test), elevation(test) });
		}
		std::cout << visited.size() << " " << nodes.size() << " " << m << std::endl;
	}
	std::cout << "Error\n";
}

void Part1::printResult() {
    std::cout << "Result: " << result << std::endl;
}