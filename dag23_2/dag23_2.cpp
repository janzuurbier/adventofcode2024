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

	set<string> computers;
	for (auto it = m.begin(); it != m.end(); it++ )
		computers.insert(it->first);

	vector<set<string>> groups;
	while (!computers.empty()) {
		string s = *computers.begin();
		computers.erase(computers.begin());
		set<string> group;
		group.insert(s);
		
		for (auto it = computers.begin(); it != computers.end(); ) {
			bool b = true;
			for (string u : group)
				if (m[u].count(*it) == 0 || m[*it].count(u) == 0)
					b = false;
			if (b) {
				group.insert(*it);
				it = computers.erase(it);
			}
			else
				it++;
		}
		groups.push_back(group);
	}

	int max = 0;
	for (set<string> g : groups) {
		for (string s : g)
			cout << s << ",";
		cout << "  (" << g.size() << ")" << endl;
		if (g.size() > max)
			max = g.size();
	}


	

}

