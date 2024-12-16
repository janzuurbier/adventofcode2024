
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

int max(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
}

bool can_move_up(matrix<char>& m, int i, int j) {
	if (m[i - 1][j] == '#')
		return false;
	if (m[i - 1][j] == '.')
		return true;
	if (m[i - 1][j] == '[')
		return can_move_up(m, i - 1, j) && can_move_up(m, i - 1, j + 1);
	if (m[i - 1][j] == ']')
		return can_move_up(m, i - 1, j) && can_move_up(m, i - 1, j - 1);
}

bool can_move_down(matrix<char>& m, int i, int j) {
	if (m[i + 1][j] == '#')
		return false;
	if (m[i + 1][j] == '.')
		return true;
	if (m[i + 1][j] == '[')
		return can_move_down(m, i + 1, j) && can_move_down(m, i + 1, j + 1);
	if (m[i + 1][j] == ']')
		return can_move_down(m, i + 1, j) && can_move_down(m, i + 1, j - 1);
}


int count_rows_up(matrix<char>& m, int i, int j) {
	if (m[i - 1][j] == '#')
		return 0;
	if (m[i - 1][j] == '.')
		return 1;
	if (m[i - 1][j] == '[')
		return 1 + max(count_rows_up(m, i - 1,j) , count_rows_up(m, i - 1, j + 1));
	if (m[i - 1][j] == ']')
		return 1 + max(count_rows_up(m, i - 1, j), count_rows_up(m, i - 1, j - 1));
}

int count_rows_down(matrix<char>& m, int i, int j) {
	if (m[i + 1][j] == '#')
		return 0;
	if (m[i + 1][j] == '.')
		return 1;
	if (m[i + 1][j] == '[')
		return 1 + max(count_rows_down(m, i + 1, j), count_rows_down(m, i + 1, j + 1));
	if (m[i + 1][j] == ']')
		return 1 + max(count_rows_down(m, i + 1, j), count_rows_down(m, i + 1, j - 1));
}

void move_up(matrix<char>& m, int i, int j, int n) {
	vector<point> v;
	set<point> w;
	set<point> u;
	v.push_back(point(i, j));
	w.insert(point(i, j));
	for (int k = 0; k < n; k++) {
		u.clear();
		for (point p : w) {
			if (m[p.first - 1][p.second] == '[') {
				u.insert(point(p.first - 1, p.second));
				u.insert(point(p.first - 1, p.second + 1));
				v.push_back(point(p.first - 1, p.second));
				v.push_back(point(p.first - 1, p.second + 1));
			}
			if (m[p.first - 1][p.second] == ']') {
				if (u.insert(point(p.first - 1, p.second)).second)
					v.push_back(point(p.first - 1, p.second));
				if (u.insert(point(p.first - 1, p.second - 1)).second)
					v.push_back(point(p.first - 1, p.second - 1));
			}
		}
		w = u;
	}
	while (!v.empty()) {
		point p = v.back();
		m[p.first - 1][p.second] = m[p.first][p.second];
		m[p.first][p.second] = '.';
		v.pop_back();
	}
}

void move_down(matrix<char>& m, int i, int j, int n) {
	vector<point> v;
	set<point> w;
	set<point> u;
	v.push_back(point(i, j));
	w.insert(point(i, j));
	for (int k = 0; k < n; k++) {
		u.clear();
		for (point p : w) {
			if (m[p.first + 1][p.second] == '[') {
				u.insert(point(p.first + 1, p.second));
				u.insert(point(p.first + 1, p.second + 1));
				v.push_back(point(p.first + 1, p.second));
				v.push_back(point(p.first + 1, p.second + 1));
			}
			if (m[p.first + 1][p.second] == ']') {
				if (u.insert(point(p.first + 1, p.second)).second)
					v.push_back(point(p.first + 1, p.second));
				if (u.insert(point(p.first + 1, p.second - 1)).second)
					v.push_back(point(p.first + 1, p.second - 1));
			}
		}
		w = u;
	}
	while (!v.empty()) {
		point p = v.back();
		m[p.first + 1][p.second] = m[p.first][p.second];
		m[p.first][p.second] = '.';
		v.pop_back();
	}
}
	



int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	matrix<char> temp;
	input >> temp;

	matrix<char> m(temp.getRows(), temp.getCols() * 2, '.');
	for (int i = 0; i < temp.getRows(); i++)
		for (int j = 0; j < temp.getCols(); j++) {
			if (temp[i][j] == '#') {
				m[i][2 * j] = '#';
				m[i][2 * j + 1] = '#';
			}
			if (temp[i][j] == '.') {
				m[i][2 * j] = '.';
				m[i][2 * j + 1] = '.';
			}
			if (temp[i][j] == '@') {
				m[i][2 * j] = '@';
				m[i][2 * j + 1] = '.';
			}
			if (temp[i][j] == 'O') {
				m[i][2 * j] = '[';
				m[i][2 * j + 1] = ']';
			}
		}
	int xpos = 0, ypos = 0;
	for (int i = 0; i < m.getRows(); i++)
		for (int j = 0; j < m.getCols(); j++)
			if (m[i][j] == '@') {
				xpos = j;
				ypos = i;
			}


	char ch;
	//ofstream output("C:\\Users\\Jan\\Desktop\\output.txt");
	while (input >> ch) {
		//output << m << endl;
		//output << "Move " << ch << ":" << endl;

		if (ch == '^' && can_move_up(m, ypos, xpos)){
			int n = count_rows_up(m, ypos, xpos); 
			move_up(m, ypos, xpos, n);
			ypos--;
		}
		if (ch == 'v' && can_move_down(m, ypos, xpos)) {
			int n = count_rows_down(m, ypos, xpos);
			move_down(m, ypos, xpos, n);
			ypos++;
		}
		if (ch == '>') {
			if (m[ypos][xpos + 1] == '#')
				continue;
			if (m[ypos][xpos + 1] == '.') {
				m[ypos][xpos] = '.';
				xpos++;
				m[ypos][xpos] = '@';
				continue;
			}
			if (m[ypos][xpos + 1] == '[') {
				int i = xpos + 1;
				while (m[ypos][i] == '[' || m[ypos][i] == ']')
					i++;
				if (m[ypos][i] == '#')
					continue;
				if (m[ypos][i] == '.') {
					while (i > xpos) {
						m[ypos][i] = ']';
						i--;
						m[ypos][i] = '[';
						i--;
					}
					m[ypos][xpos] = '.';
					xpos++;
					m[ypos][xpos] = '@';

				}
				continue;
			}
		}
		if (ch == '<') {
			if (m[ypos][xpos - 1] == '#')
				continue;
			if (m[ypos][xpos - 1] == '.') {
				m[ypos][xpos] = '.';
				xpos--;
				m[ypos][xpos] = '@';
				continue;
			}
			if (m[ypos][xpos - 1] == ']') {
				int i = xpos - 1;
				while (m[ypos][i] == '[' || m[ypos][i] == ']')
					i--;
				if (m[ypos][i] == '#')
					continue;
				if (m[ypos][i] == '.') {
					while (i < xpos) {
						m[ypos][i] = '[';
						i++;
						m[ypos][i] = ']';
						i++;
					}
					m[ypos][xpos] = '.';
					xpos--;
					m[ypos][xpos] = '@';
				}
				continue;
			}
		}
	}//while
	//cout << m << endl;
	int sum = 0;
	for (int i = 0; i < m.getRows(); i++)
		for (int j = 0; j < m.getCols(); j++)
			if (m[i][j] == '[')
				sum += 100 * i + j;
	cout << sum << endl;
}

