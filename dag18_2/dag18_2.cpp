
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

enum dir_t { E, N, S, W };
typedef tuple<int, int> vertex;
map<vertex, int> dist_map;
set<vertex> visited;
priority_queue<vertex, vector<vertex>, bool(*)(const vertex& a, const vertex& b)> todo([](const vertex& a, const vertex& b) { return dist_map[a] > dist_map[b]; });

const int ROWS = 71;
const int COLS = 71;
matrix<char> m(ROWS, COLS, '.');
int NR_CORRUPTED = 3000; //adjusted after program toke to long

void mark_neighbours(const vertex& v) {
	int row = get<0>(v);
	int col = get<1>(v);
	vector<vertex> neighbours;
	if (m.isInRange(row + 1, col) && m[row + 1][col] != '#')
		neighbours.push_back(vertex(row + 1, col));
	if (m.isInRange(row - 1, col) && m[row - 1][col] != '#')
		neighbours.push_back(vertex(row - 1, col));
	if (m.isInRange(row, col - 1) && m[row][col - 1] != '#')
		neighbours.push_back(vertex(row, col - 1));
	if (m.isInRange(row, col + 1) && m[row][col + 1] != '#')
		neighbours.push_back(vertex(row, col + 1));
	for (vertex w : neighbours) {
		if (visited.count(w) == 0)
			if (dist_map.count(w) == 0) {
				dist_map[w] = dist_map[v] + 1;
				todo.push(w);
			}
			else
				if (dist_map[v] + 1 < dist_map[w]) {
					dist_map[w] = dist_map[v] + 1;
				}
	}
}


int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	string line;
	for (int i = 0; i < NR_CORRUPTED; i++) {
		getline(input, line);
		stringstream ss(line);
		int r, c;
		char ch;
		ss >> c >> ch >> r;
		m[r][c] = '#';
	}

	vertex start = vertex(0, 0);
	todo.push(start);
	dist_map[start] = 0;
	while (!todo.empty()) {
		vertex v = todo.top();
		int row = get<0>(v);
		int col = get<1>(v);
		todo.pop();
		mark_neighbours(v);
		visited.insert(v);
		if (row == ROWS - 1 && col == COLS - 1) {
			cout << dist_map[v] << endl;
			break;
		}
	}

	while (getline(input, line)) {
		stringstream ss(line);
		int r, c;
		char ch;
		ss >> c >> ch >> r;
		m[r][c] = '#';
		cout << "(" << c << ", " << r << ") falling: ";

		while (!todo.empty())
			todo.pop();
		visited.clear();
		dist_map.clear();
		vertex start = vertex(0, 0);
		todo.push(start);
		dist_map[start] = 0;
		bool path_found = false;
		while (!todo.empty()) {
			vertex v = todo.top();
			int row = get<0>(v);
			int col = get<1>(v);
			todo.pop();
			mark_neighbours(v);
			visited.insert(v);
			if (row == ROWS - 1 && col == COLS - 1) {
				cout << dist_map[v] << endl;
				path_found = true;
				break;
			}
		}
		if (!path_found) {
			cout << "no path found" << endl;
			break;
		}
	}
}
