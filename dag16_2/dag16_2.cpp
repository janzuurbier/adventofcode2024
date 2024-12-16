

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
typedef tuple<int, int, dir_t> vertex;
map<vertex, int> dist_map;
map<vertex, vector<vertex>> pred_map;
set<vertex> visited;
priority_queue<vertex, vector<vertex>, bool(*)(const vertex& a, const vertex& b)> todo([](const vertex& a, const vertex& b) { return dist_map[a] > dist_map[b]; });
matrix<char> m;

void mark_neighbours(const vertex& v) {
	int row = get<0>(v);
	int col = get<1>(v);
	dir_t dir = get<2>(v);
	vector<pair<vertex, int>> neighbours;
	switch (dir) {
	case E:
		if (m[row][col + 1] != '#') {
			vertex w(row, col + 1, E);
			neighbours.push_back(pair<vertex, int>(w, 1));
		}
		if (m[row - 1][col] != '#') {
			vertex w(row, col, N);
			neighbours.push_back(pair<vertex, int>(w, 1000));
		}
		if (m[row + 1][col] != '#') {
			vertex w(row, col, S);
			neighbours.push_back(pair<vertex, int>(w, 1000));
		}
		break;
	case W:
		if (m[row][col - 1] != '#') {
			vertex w(row, col - 1, W);
			neighbours.push_back(pair<vertex, int>(w, 1));
		}
		if (m[row - 1][col] != '#') {
			vertex w(row, col, N);
			neighbours.push_back(pair<vertex, int>(w, 1000));
		}
		if (m[row + 1][col] != '#') {
			vertex w(row, col, S);
			neighbours.push_back(pair<vertex, int>(w, 1000));
		}
		break;
	case S:
		if (m[row + 1][col] != '#') {
			vertex w(row + 1, col, S);
			neighbours.push_back(pair<vertex, int>(w, 1));
		}
		if (m[row][col - 1] != '#') {
			vertex w(row, col, W);
			neighbours.push_back(pair<vertex, int>(w, 1000));
		}
		if (m[row][col + 1] != '#') {
			vertex w(row, col, E);
			neighbours.push_back(pair<vertex, int>(w, 1000));
		}
		break;
	case N:
		if (m[row - 1][col] != '#') {
			vertex w(row - 1, col, N);
			neighbours.push_back(pair<vertex, int>(w, 1));
		}
		if (m[row][col - 1] != '#') {
			vertex w(row, col, W);
			neighbours.push_back(pair<vertex, int>(w, 1000));
		}
		if (m[row][col + 1] != '#') {
			vertex w(row, col, E);
			neighbours.push_back(pair<vertex, int>(w, 1000));
		}
		break;
	}
	for (pair<vertex, int>& p : neighbours) {
		vertex& w = p.first;
		if (visited.count(w) == 0)
			if (dist_map.count(w) == 0) {
				dist_map[w] = dist_map[v] + p.second;
				todo.push(w);
				pred_map[w].push_back(v);
			}
			else
				if (dist_map[v] + p.second < dist_map[w]) {
					dist_map[w] = dist_map[v] + p.second;
					pred_map[w].clear();
					pred_map[w].push_back(v);
				}
				else
					if (dist_map[v] + p.second == dist_map[w]) {
						dist_map[w] = dist_map[v] + p.second;
						pred_map[w].push_back(v);
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
	input >> m;
	vertex start = vertex(m.getRows() - 2, 1, E);
	todo.push(start);
	dist_map[start] = 0;

	while (!todo.empty()) {
		vertex v = todo.top();
		int row = get<0>(v);
		int col = get<1>(v);
		int dist = dist_map[v];
		todo.pop();
		mark_neighbours(v);
		visited.insert(v);
		if (m[row][col] == 'E') {
			//cout << dist << endl;
			vector<vertex> vv;
			vv.push_back(v);
			while (!vv.empty()) {
				v = vv.back();
				vv.pop_back();
				for (vertex w : pred_map[v])
					vv.push_back(w);
				row = get<0>(v);
				col = get<1>(v);
				m[row][col] = 'O';
			}
			//cout << m << endl;
			int sum = 0;
			for (int i = 0; i < m.getRows(); i++)
				for (int j = 0; j < m.getCols(); j++)
					if (m[i][j] == 'O')
						sum++;
			cout << sum << endl;
			return 0;
		}
	}
	cout << "no path found" << endl;
}
