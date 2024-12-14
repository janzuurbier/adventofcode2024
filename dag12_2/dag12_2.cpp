// dag12_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <set>
#include "../../adventofcode2023/matrix_new/matrix.h"
using namespace std;

typedef pair<int, int> point;

point left(point p) {
	return point(p.first, p.second - 1);
}

point right(point p) {
	return point(p.first, p.second + 1);
}

point above(point p) {
	return point(p.first -1, p.second);
}

point under(point p) {
	return point(p.first + 1, p.second);
}

bool is_top_border(const set<point>& s, const point& p) {
	return s.count(p) > 0 && s.count(above(p)) == 0;
}

bool is_left_border(const set<point>& s, const point& p) {
	return s.count(p) > 0 && s.count(left(p)) == 0;
}

bool is_right_border(const set<point>& s, const point& p) {
	return s.count(p) > 0 && s.count(right(p)) == 0;
}

bool is_down_border(const set<point>& s, const point& p) {
	return s.count(p) > 0 && s.count(under(p)) == 0;
}

int count_sides(set<point> region) {
	int sides = 0;
	for (point p : region) {
		if (is_top_border(region, p)&& !is_top_border(region, left(p)))
			sides++;
		if (is_left_border(region, p)&& !is_left_border(region, under(p)))
			sides++;
		if (is_down_border(region, p) && !is_down_border(region, right(p)))
			sides++;
		if (is_right_border(region, p) && !is_right_border(region, above(p)))
			sides++;
	}
	return sides;
}


int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}
	matrix<char> m;
	input >> m;
	matrix<bool> marked(m.getRows(), m.getCols(), false);
	int total_price = 0;

	for (int i = 0; i < m.getRows(); i++)
		for (int j = 0; j < m.getCols(); j++)
			if (!marked[i][j]) {
				marked[i][j] = true;
				char ch = m[i][j];
				set<point> region;
				set<point> s;
				s.insert(point(i, j));
				region.insert(point(i, j));
				while (!s.empty()) {
					set<point> t;
					for (point p : s) {
						if (m.isInRange(p.first - 1, p.second) && m[p.first - 1][p.second] == ch && !marked[p.first - 1][p.second]) {
							t.insert(point(p.first - 1, p.second));
							marked[p.first - 1][p.second] = true;
							region.insert(point(p.first - 1, p.second));
						}
						if (m.isInRange(p.first + 1, p.second) && m[p.first + 1][p.second] == ch && !marked[p.first + 1][p.second]) {
							t.insert(point(p.first + 1, p.second));
							marked[p.first + 1][p.second] = true;
							region.insert(point(p.first + 1, p.second));
						}
						if (m.isInRange(p.first, p.second - 1) && m[p.first][p.second - 1] == ch && !marked[p.first][p.second - 1]) {
							t.insert(point(p.first, p.second - 1));
							marked[p.first][p.second - 1] = true;
							region.insert(point(p.first, p.second - 1));
						}
						if (m.isInRange(p.first, p.second + 1) && m[p.first][p.second + 1] == ch && !marked[p.first][p.second + 1]) {
							t.insert(point(p.first, p.second + 1));
							marked[p.first][p.second + 1] = true;
							region.insert(point(p.first, p.second + 1));
						}
					}
					s = t;
				}
				cout << ch << ": " << region.size() << " * ";
				int sides = count_sides(region);	
				cout << sides << " = " << region.size() * sides << endl;
				total_price += region.size() * sides;
			}
	cout << total_price;
}

