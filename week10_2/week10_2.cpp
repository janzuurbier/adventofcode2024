// week10_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
typedef vector<point> trail;

int find_nr_trails(point p) {
	set<trail> v;
	trail t;
	t.push_back(p);
	v.insert(t);
	for (char h = '0'; h < '9'; h++) {
		set<trail> w;
		for (trail t : v) {
			point p = t.back();
			if (m.isInRange(p.first - 1, p.second) && m[p.first - 1][p.second] == h + 1) {
				t.push_back(point(p.first - 1, p.second));
				w.insert(t);
			}
			if (m.isInRange(p.first + 1, p.second) && m[p.first + 1][p.second] == h + 1) {
				t.push_back(point(p.first + 1, p.second));
				w.insert(t);
			}
			if (m.isInRange(p.first, p.second - 1) && m[p.first][p.second - 1] == h + 1) {
				t.push_back(point(p.first, p.second - 1));
				w.insert(t);
			}
			if (m.isInRange(p.first, p.second + 1) && m[p.first][p.second + 1] == h + 1) {
				t.push_back(point(p.first, p.second + 1));
				w.insert(t);
			}
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
				sum += find_nr_trails(point(i, j));
				cout << find_nr_trails(point(i, j)) << ", ";
			}
	cout << endl << sum << endl;

}

