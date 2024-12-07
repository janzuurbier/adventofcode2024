// week6_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <tuple>
#include <set>
#include "../../adventofcode2023/matrix_new/matrix.h"

using namespace std;

enum dir_t { UP, RIGHT, DOWN, LEFT };

matrix<char> map;
int row_start = 0;
int col_start = 0;
int row = 0;
int col = 0;
dir_t dir = UP;


void turn_right() {
	switch (dir) {
	case UP: dir = RIGHT; break;
	case RIGHT: dir = DOWN; break;
	case DOWN: dir = LEFT; break;
	case LEFT: dir = UP; break;
	}
}

bool move() {
	switch (dir) {
	case UP:
		if (!map.isInRange(row - 1, col))
			return false;
		if (map[row - 1][col] == '#') 
			turn_right();	
		else
			row--;
		break;
	case RIGHT:
		if (!map.isInRange(row, col + 1))
			return false;
		if (map[row][col + 1] == '#')
			turn_right();
		else
			col++;
		break;
	case DOWN:
		if (!map.isInRange(row + 1, col))
			return false;
		if (map[row + 1][col] == '#')
			turn_right();
		else
			row++;
		break;
	case LEFT:
		if (!map.isInRange(row, col - 1))
			return false;
		if (map[row][col - 1] == '#')
			turn_right();
		else
			col--;
		break;
	}
	return true;
}


int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	input >> map;

	for (int i = 0; i < map.getRows(); i++)
		for (int j = 0; j < map.getCols(); j++)
			if (map[i][j] == '^') {
				row_start = i;
				col_start = j;
			}

	set<pair<int, int>> poss_obstr;
	//same as part 1
	//this are also possible places to put an obstruction
	//but no obstruction in starting position
	row = row_start;
	col = col_start;
	while (move()) {
		poss_obstr.insert(pair<int, int>(row, col));
	}
	cout << poss_obstr.size() << endl;

	int number = 0;
	for (pair<int, int> p : poss_obstr) {
		int i = p.first;
		int j = p.second;
		map[i][j] = '#';
		
		row = row_start;
		col = col_start;
		dir = UP;
		set<tuple<int, int, dir_t>> visited;
		while (move()) {
			if (!visited.insert(make_tuple(row, col, dir)).second) {
				number++;
				break;
			}
		}
		map[i][j] = '.';
		
	}
	
	cout << number << endl;
}


