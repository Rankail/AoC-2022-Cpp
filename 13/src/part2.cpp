#include "part2.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

static std::vector<std::string> stringToTokens(const std::string& s) {
	auto tokens = std::vector<std::string>();
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == ',') continue;
		if (s[i] == '[' || s[i] == ']') {
			tokens.push_back(std::string(1, s[i]));
			continue;
		}
		int idx = s.find_first_of("[],", i);
		tokens.push_back(s.substr(i, idx - i));
		i = idx - 1;
	}
	return tokens;
}

bool compare(const std::string& a, const std::string& b) {
	std::vector<std::string> as = stringToTokens(a);
	std::vector<std::string> bs = stringToTokens(b);

	int i = 0;
	int j = 0;
	while (true) {
		if (i >= as.size()) {
			return true;
		} else if (j >= bs.size()) {
			return false;
		}
		if (as[i] == bs[j] && (as[i] == "[" || as[i] == "]")) {
			i++;
			j++;
			continue;
		}
		if (as[i] == "]") {
			return true;
		} else if (bs[j] == "]") {
			return false;
		}

		if (as[i] == "[") {
			i++;
			bs.insert(bs.begin() + j + 1, "]");
			continue;
		} else if (bs[j] == "[") {
			j++;
			as.insert(as.begin() + i + 1, "]");
			continue;
		}

		int an = std::stoi(as[i]);
		int bn = std::stoi(bs[j]);
		if (an != bn) {
			return an < bn;
		}
		i++;
		j++;
	}
	return false;
}

void Part2::run(std::ifstream& file) {
	std::vector<std::string> lines = std::vector<std::string>();
	std::string line;
	while (std::getline(file, line)) {
		if (line.empty()) continue;
		lines.push_back(line);
	}
	lines.push_back("[[2]]");
	lines.push_back("[[6]]");

	std::sort(lines.begin(), lines.end(), compare);

	auto ai = std::distance(lines.begin(), std::find(lines.begin(), lines.end(), "[[2]]"));
	auto bi = std::distance(lines.begin(), std::find(lines.begin(), lines.end(), "[[6]]"));
	result = (ai+1) * (bi+1);
}

void Part2::printResult() {
    std::cout << "Result: " << result << std::endl;
}