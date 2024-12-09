// week8_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

	matrix<char> antenna_map;
	input >> antenna_map;

	map<char, vector<point>> points_per_freq;
	set<point> antinodes;

	for (int i = 0; i < antenna_map.getRows(); i++)
		for (int j = 0; j < antenna_map.getCols(); j++)
			if (antenna_map[i][j] != '.') {
				points_per_freq.insert(pair<char, vector<point>>(antenna_map[i][j], vector<point>()));
			}
	for (int i = 0; i < antenna_map.getRows(); i++)
		for (int j = 0; j < antenna_map.getCols(); j++)
			if (antenna_map[i][j] != '.') {
				points_per_freq[antenna_map[i][j]].push_back(point(i, j));
			}
	for (auto it = points_per_freq.begin(); it != points_per_freq.end(); ++it) {
		vector<point> v = it->second;
		for (int i = 0; i < v.size(); i++)
			for (int j = i + 1; j < v.size(); j++) {
				int a = v[i].first - v[j].first;
				int b = v[i].second - v[j].second;
				int k = 0;
				while (antenna_map.isInRange(v[i].first + k * a, v[i].second + k * b)) {
					antinodes.insert(point(v[i].first + k * a, v[i].second + k * b));
					k++;
				}
				k = 0;
				while (antenna_map.isInRange(v[j].first - k * a, v[j].second - k * b)) {
					antinodes.insert(point(v[j].first - k * a, v[j].second - k * b));
					k++;
				}

			}
	}
	cout << antinodes.size() << endl;
	/*for (point p : antinodes)
		antenna_map[p.first][p.second] = '#';
	cout << antenna_map << endl;*/

}
