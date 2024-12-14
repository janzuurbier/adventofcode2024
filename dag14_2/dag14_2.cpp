
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include "../../adventofcode2023/matrix_new/matrix.h"
using namespace std;

typedef pair<int, int> point;

const int WIDTH = 101;
const int HEIGHT = 103;





int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	map<point, int> m;
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
			m[point(i, j)] = 0;

	vector<point> pos_vect;
	vector<point> v_vect;

	while (input) {
		string line;
		int xpos, ypos, vx, vy;
		char ch;
		input >> ch >> ch >> xpos >> ch >> ypos;
		input >> ch >> ch >> vx >> ch >> vy;
		getline(input, line);

		pos_vect.push_back(point(xpos, ypos));
		v_vect.push_back(point(vx, vy));
	}

	int seconds = 0;
	while (true) {
		seconds++;
		for (int i = 0; i < pos_vect.size(); i++) {
			pos_vect[i].first += v_vect[i].first;
			pos_vect[i].first %= WIDTH;
			if (pos_vect[i].first < 0) pos_vect[i].first += WIDTH;
			pos_vect[i].second += v_vect[i].second;
			pos_vect[i].second %= HEIGHT;
			if (pos_vect[i].second < 0) pos_vect[i].second += HEIGHT;
		}
		
		//try and find a cluster of 9 robots
		matrix<char> tiles(WIDTH, HEIGHT, '.');
		for (point p : pos_vect)
			tiles[p.first][p.second] = '#';	
		for (point p : pos_vect) {
			int count = 0;
			for (int i = -1; i <= 1; i++)
				for (int j = -1; j <= 1; j++)
					if (tiles.isInRange(p.first + i, p.second + j) && tiles[p.first + i][p.second + j] == '#')
						count++;
			if (count == 9) {
				cout << tiles << endl;
				cout << seconds << endl;
			}
		}
	}
}

