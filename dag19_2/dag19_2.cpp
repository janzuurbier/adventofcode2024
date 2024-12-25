
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

vector<string> available_patterns;
map<int, vector<string>> patterns_by_size;

bool starts_with(string s, string t) {
	size_t n = t.size();
	return (s.substr(0, n) == t);
}

int min(int a, int b) {
	if (a < b)
		return a;
	else
		return b;
}

map<int, uint64_t> look_up;

uint64_t hulp(string pattern) {
	uint64_t n = 0;
	for(string s: available_patterns){
		if (starts_with(pattern, s))
			n += look_up[pattern.size() - s.size()];
	}
	return n;
}

uint64_t nr_possibilities(string desired_pattern) {
	look_up.clear();
	look_up[0] = 1;
	for (int i = 1; i <= desired_pattern.size(); i++) {
		look_up[i] = hulp(desired_pattern.substr(desired_pattern.size() - i));
	}
	return look_up[desired_pattern.size() ];
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
	//sort(available_patterns.begin(), available_patterns.end(), [](const string& a, const string& b) {return a.size() > b.size(); });
	for (string s : available_patterns)
		patterns_by_size[s.size()].push_back(s);

	string p;
	uint64_t sum = 0;
	while (input >> p) {
		uint64_t n = nr_possibilities(p);
		cout << p << ": " << n << endl;
		sum += n;
	}
	cout << sum << endl;
}

