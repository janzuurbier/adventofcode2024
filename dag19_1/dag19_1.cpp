
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include "../../adventofcode2023/matrix_new/matrix.h"
using namespace std;

vector<string> available_patterns;

bool starts_with(string s, string t) {
	size_t n = t.size();
	return (s.substr(0, n) == t);
}


bool is_possible(string desired_pattern) {
	if (desired_pattern.size() == 0)
		return true;
	for (string s : available_patterns) {
		if (starts_with(desired_pattern, s)) {
			if (is_possible(desired_pattern.substr(s.size())))
				return true;
		}
	}
	return false;

}

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}
	string line;
	getline(input, line);
	stringstream ss(line);
	string pattern;
	while (ss >> pattern) {
		if (pattern[pattern.size() - 1] == ',')
			pattern = pattern.substr(0, pattern.size() - 1);
		available_patterns.push_back(pattern);
	}
	
	string p;
	int sum = 0;
	while (input >> p) {
		if ((is_possible(p))) {
			cout << p << ": yes" << endl;
			sum++;
		}
		else
			cout << p << ": no" << endl;
	}
	cout << sum << endl;

}

