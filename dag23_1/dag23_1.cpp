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

map<string, set<string>> m;

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}
	string line;
	while (getline(input, line)) {
		size_t pos = line.find('-');
		string a = line.substr(0, pos);
		string b = line.substr(pos + 1);
		m[a].insert(b);
		m[b].insert(a);
	}

	int sum = 0;
	for (auto it = m.begin(); it != m.end(); it++)
		for (string s : it->second)
			for (string t : m[s])
				if (m[t].count(it->first) > 0) {
					if (it->first[0] == 't' ||
						s[0] == 't' ||
						t[0] == 't') {
						//cout << it->first << ", " << s << ", " << t << endl;
						sum++;
					}
				}
	cout << sum/6 << endl;
		
	
}

