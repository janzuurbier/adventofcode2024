
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

matrix<char> m;
typedef pair<int, int> point;

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}
	
	input >> m;
	matrix<int> n(m.getRows(), m.getCols(), -1);

	int rStart = 0;
	int cStart = 0;
	for (int i = 0; i < m.getRows(); i++)
		for (int j = 0; j < m.getCols(); j++)
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

	vector<int> cheats;
	for (int i = 0; i <= picosec; i++)
		cheats.push_back(0);
	
	for (int i = 0; i < track.size(); i++)
		for (int j = i + 100; j < track.size(); j++) {
			int manhatan_len = abs(track[j].first - track[i].first) + abs(track[j].second - track[i].second);
			if (manhatan_len <= 20) {				
					cheats[j - i - manhatan_len] += 1;
			}
		}
	
	int sum = 0;
	for (int i = 100; i < cheats.size(); i++) {
		if (cheats[i] > 0) {
			cout << "There are " << cheats[i] << " cheats that save "
				<< i << " picoseconds" << endl;
			sum += cheats[i];
		}
	}
	cout << sum << endl;

}

