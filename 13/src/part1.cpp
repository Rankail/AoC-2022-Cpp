#include "part1.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

static std::vector<std::string> stringToTokens(const std::string& s) {
	auto tokens = std::vector<std::string>();
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == ',') continue;
		if (s[i] == '[' || s[i] == ']') {
			tokens.push_back(std::string(1, s[i]));
			continue;
		}
		int idx = s.find_first_of("[],", i);
		tokens.push_back(s.substr(i, idx-i));
		i = idx - 1;
	}
	return tokens;
}

int compare(const std::string& a, const std::string& b) {
	std::vector<std::string> as = stringToTokens(a);
	std::vector<std::string> bs = stringToTokens(b);
	
	int i = 0;
	int j = 0;
	while (true) {
		if (i >= as.size()) {
			return -1;
		} else if (j >= bs.size()) {
			return 1;
		}
		if (as[i] == bs[j] && (as[i] == "[" || as[i] == "]")) {
			i++;
			j++;
			continue;
		}
		if (as[i] == "]") {
			return -1;
		} else if (bs[j] == "]") {
			return 1;
		}

		if (as[i] == "[") {
			i++;
			bs.insert(bs.begin()+j+1, "]");
			continue;
		} else if (bs[j] == "[") {
			j++;
			as.insert(as.begin() + i + 1, "]");
			continue;
		}

		int an = std::stoi(as[i]);
		int bn = std::stoi(bs[j]);
		if (an != bn) {
			return an - bn;
		}
		i++;
		j++;
	}
}

void Part1::run(std::ifstream& file) {
	int sum = 0;
	int idx = 1;
	std::string a, b;
	while (std::getline(file, a)) {
		std::getline(file, b);

		if (compare(a, b) < 0) {
			sum += idx;
		}

		std::getline(file, b);

		idx++;
	}

	result = sum;
}

void Part1::printResult() {
    std::cout << "Result: " << result << std::endl;
}