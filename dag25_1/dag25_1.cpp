#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <set>
#include <list>
#include "../../adventofcode2023/matrix_new/matrix.h"
using namespace std;

struct lock {
	int pins[5];

	lock(matrix<char>& m) {
		for (int i = 0; i < 5; i++) {
			int j = 0;
			while (m[j][i] == '#')
				j++;
			pins[i] = j - 1;
		}
	}
};

struct key {
	int heights[5];

	key(matrix<char>& m) {
		for (int i = 0; i < 5; i++) {
			int j = 0;
			while (m[j][i] == '.')
				j++;
			heights[i] = 6 - j;
		}
	}

	bool fits(const lock& l) {
		for (int i = 0; i < 5; i++) {
			if (heights[i] + l.pins[i] > 5)
				return false;
		}
		return true;
	}
};

vector<lock> locks;
vector<key> keys;

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	matrix<char> m;
	while (input) {
		input >> m;
		bool is_lock = (m[0][0] == '#') && (m[0][1] == '#') &&
			(m[0][2] == '#') && (m[0][3] == '#') && (m[0][4] == '#');
		if (is_lock)
			locks.push_back(m);
		else
			keys.push_back(m);
	}

	cout << locks.size() << " locks and " << keys.size() << " keys." << endl;

	int sum = 0;
	for(key k : keys)
		for (lock l : locks) {
			if (k.fits(l))
				sum++;
		}
	cout << sum << endl;
}

