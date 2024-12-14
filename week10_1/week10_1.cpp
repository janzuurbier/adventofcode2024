// week10_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include "../../adventofcode2023/matrix_new/matrix.h"
using namespace std;

matrix<char> m;

typedef pair<int, int> point;

int find_nr_paths(point p) {
	set<point> v;
	v.insert(p);
	for (char h = '0'; h < '9'; h++) {
		set<point> w;
		for (point p : v) {
			if (m.isInRange(p.first - 1, p.second) && m[p.first - 1][p.second] == h + 1)
				w.insert(point(p.first - 1, p.second));
			if (m.isInRange(p.first + 1, p.second) && m[p.first + 1][p.second] == h + 1)
				w.insert(point(p.first + 1, p.second));
			if (m.isInRange(p.first, p.second - 1) && m[p.first][p.second - 1] == h + 1)
				w.insert(point(p.first, p.second - 1));
			if (m.isInRange(p.first, p.second + 1) && m[p.first][p.second + 1] == h + 1)
				w.insert(point(p.first, p.second + 1));
		}
		v = w;
	}
	return v.size();
}




int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}
	input >> m;
	int sum = 0;
	for (int i = 0; i < m.getRows(); i++)
		for (int j = 0; j < m.getCols(); j++)
			if (m[i][j] == '0') {
				sum += find_nr_paths(point(i, j));
				cout << find_nr_paths(point(i, j)) << "\t";
			}
	cout << endl << sum << endl;

}

