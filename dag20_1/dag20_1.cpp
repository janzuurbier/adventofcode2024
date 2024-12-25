
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
	matrix<int> n(m.getRows(), m.getCols(), -1);

	int rStart = 0;
	int cStart = 0;
	for(int i = 0; i < m.getRows(); i++)
		for(int j = 0; j < m.getCols(); j++)
			if (m[i][j] == 'S') {
				rStart = i;
				cStart = j;
			}

	int r = rStart;
	int c = cStart;
	int picosec = 0;
	n[r][c] = picosec;
	vector<point> track;
	track.push_back(point(r, c));
	while (m[r][c] != 'E') {
		if (m[r + 1][c] != '#' && n[r + 1][c] == -1)
			r = r + 1;
		else if (m[r - 1][c] != '#' && n[r - 1][c] == -1)
			r = r - 1;
		else if (m[r][c + 1] != '#' && n[r][c + 1] == -1)
			c = c + 1;
		else if (m[r][c - 1] != '#' && n[r][c - 1] == -1)
			c = c - 1;
		picosec++;
		n[r][c] = picosec;
		track.push_back(point(r, c));
	}

	cout << picosec << endl;

	vector<int> cheats;
	for (int i = 0; i < picosec; i++)
		cheats.push_back(0);

	for(point p : track) {
		int r = p.first;
		int c = p.second;
		if (m[r + 1][c] == '#' && m.isInRange(r + 2, c)
			&& m[r + 2][c] != '#' && n[r + 2][c] > n[r][c])
			cheats[n[r + 2][c] - n[r][c] - 2]++;
		if (m[r - 1][c] == '#' && m.isInRange(r - 2, c)
			&& m[r - 2][c] != '#' && n[r - 2][c] > n[r][c])
			cheats[n[r - 2][c ] - n[r][c] - 2]++;
		if (m[r][c + 1] == '#' && m.isInRange(r, c + 2)
			&& m[r][c + 2] != '#' && n[r][c + 2] > n[r][c])
			cheats[n[r][c + 2] - n[r][c] - 2]++;
		if (m[r][c - 1] == '#' && m.isInRange(r, c - 2)
			&& m[r][c - 2] != '#' && n[r][c - 2] > n[r][c])
			cheats[n[r][c - 2] - n[r][c] - 2]++;
	}

	int sum = 0;
	for(int i = 100; i < cheats.size(); i++){
		if (cheats[i] > 0) {
			cout << "There are " << cheats[i] << " cheats that save "
				<< i << " picoseconds" << endl;
			sum += cheats[i];
		}
	}
	cout << sum << endl;
}

