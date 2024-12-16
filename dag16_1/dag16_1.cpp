

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

enum dir_t{E, N, S, W};
typedef tuple<int, int, dir_t> vertex;
map<vertex, int> dist_map;
set<vertex> visited;
priority_queue<vertex, vector<vertex>, bool(*)(const vertex& a, const vertex& b)> todo([](const vertex& a, const vertex& b) { return dist_map[a] > dist_map[b]; });
matrix<char> m;

void mark_neighbours(const vertex& v) {
	int row = get<0>(v);
	int col = get<1>(v);
	dir_t dir = get<2>(v);
	switch (dir) {
	case E:
		if (m[row][col + 1] != '#') {
			vertex w(row, col + 1, E);
			if(visited.count(w) == 0)
				if (dist_map.count(w) == 0)  {
					dist_map[w] = dist_map[v] + 1;
					todo.push(w);
				}
				else
					if(dist_map[v] + 1 < dist_map[w])
						dist_map[w] = dist_map[v] + 1;

		}
		if (m[row - 1][col] != '#') {
			vertex w(row, col, N);
			if (visited.count(w) == 0)
				if (dist_map.count(w) == 0) {
					dist_map[w] = dist_map[v] + 1000;
					todo.push(w);
				}
				else
					if (dist_map[v] + 1000 < dist_map[w])
						dist_map[w] = dist_map[v] + 1000;
		}
		if (m[row + 1][col] != '#') {
			vertex w(row, col, S);
			if (visited.count(w) == 0)
				if (dist_map.count(w) == 0) {
					dist_map[w] = dist_map[v] + 1000;
					todo.push(w);
				}
				else
					if (dist_map[v] + 1000 < dist_map[w])
						dist_map[w] = dist_map[v] + 1000;
		}
		break;
	case W:
		if (m[row][col - 1] != '#') {
			vertex w(row, col - 1, W);
			if (visited.count(w) == 0)
				if (dist_map.count(w) == 0) {
					dist_map[w] = dist_map[v] + 1;
					todo.push(w);
				}
				else
					if (dist_map[v] + 1 < dist_map[w])
						dist_map[w] = dist_map[v] + 1;
		}
		if (m[row - 1][col] != '#') {
			vertex w(row, col, N);
			if (visited.count(w) == 0)
				if (dist_map.count(w) == 0) {
					dist_map[w] = dist_map[v] + 1000;
					todo.push(w);
				}
				else
					if (dist_map[v] + 1000 < dist_map[w])
						dist_map[w] = dist_map[v] + 1000;
		}
		if (m[row + 1][col] != '#') {
			vertex w(row, col, S);
			if (visited.count(w) == 0)
				if (dist_map.count(w) == 0) {
					dist_map[w] = dist_map[v] + 1000;
					todo.push(w);
				}
				else
					if (dist_map[v] + 1000 < dist_map[w])
						dist_map[w] = dist_map[v] + 1000;
		}
		break;
	case S:
		if (m[row + 1][col] != '#') {
			vertex w(row + 1, col, S);
			if (visited.count(w) == 0)
				if (dist_map.count(w) == 0) {
					dist_map[w] = dist_map[v] + 1;
					todo.push(w);
				}
				else
					if (dist_map[v] + 1 < dist_map[w])
						dist_map[w] = dist_map[v] + 1;
		}
		if (m[row ][col - 1] != '#') {
			vertex w(row, col, W);
			if (visited.count(w) == 0)
				if (dist_map.count(w) == 0) {
					dist_map[w] = dist_map[v] + 1000;
					todo.push(w);
				}
				else
					if (dist_map[v] + 1000 < dist_map[w])
						dist_map[w] = dist_map[v] + 1000;
		}
		if (m[row ][col + 1] != '#') {
			vertex w(row, col, E);
			if (visited.count(w) == 0)
				if (dist_map.count(w) == 0) {
					dist_map[w] = dist_map[v] + 1000;
					todo.push(w);
				}
				else
					if (dist_map[v] + 1000 < dist_map[w])
						dist_map[w] = dist_map[v] + 1000;
		}
		break;
	case N:
		if (m[row - 1][col] != '#') {
			vertex w(row - 1, col, N);
			if (visited.count(w) == 0)
				if (dist_map.count(w) == 0) {
					dist_map[w] = dist_map[v] + 1;
					todo.push(w);
				}
				else
					if (dist_map[v] + 1 < dist_map[w])
						dist_map[w] = dist_map[v] + 1;
		}
		if (m[row][col - 1] != '#') {
			vertex w(row, col, W);
			if (visited.count(w) == 0)
				if (dist_map.count(w) == 0) {
					dist_map[w] = dist_map[v] + 1000;
					todo.push(w);
				}
				else
					if (dist_map[v] + 1000 < dist_map[w])
						dist_map[w] = dist_map[v] + 1000;
		}
		if (m[row][col + 1] != '#') {
			vertex w(row, col, E);
			if (visited.count(w) == 0)
				if (dist_map.count(w) == 0) {
					dist_map[w] = dist_map[v] + 1000;
					todo.push(w);
				}
				else
					if (dist_map[v] + 1000 < dist_map[w])
						dist_map[w] = dist_map[v] + 1000;
		}
		break;
	}

}

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}
	input >> m;
	vertex start = vertex(m.getRows() - 2, 1, E);
	todo.push(start);
	dist_map[start] = 0;

	while (!todo.empty()) {
		vertex v = todo.top();
		int row = get<0>(v);
		int col = get<1>(v);
		int dist = dist_map[v];
		if (m[row][col] == 'E') {
			cout << dist << endl;
			return 0;
		}
		todo.pop();
		mark_neighbours(v);
		visited.insert(v);
	}
	cout << "all marked" << endl;
	


}
