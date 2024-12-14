// dag12_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

	for(int i = 0; i < m.getRows(); i++)
		for (int j = 0; j < m.getCols(); j++) 
			if(!marked[i][j]){
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
							marked[p.first - 1][ p.second] = true;
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
				int borders = 0;
				for (point p : region) {
					if (region.count(point(p.first - 1, p.second)) == 0)
						borders++;
					if (region.count(point(p.first + 1, p.second)) == 0)
						borders++;
					if (region.count(point(p.first, p.second - 1)) == 0)
						borders++;
					if (region.count(point(p.first, p.second + 1)) == 0)
						borders++;
				}
				cout << borders << " = " << region.size() * borders << endl;
				total_price += region.size() * borders;			
		}
	cout << total_price;
}

