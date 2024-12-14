
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
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
	
	while (input) {
		string line;
		int xpos, ypos, vx, vy;
		char ch;
		input >> ch >> ch >> xpos >> ch >> ypos;
		input >> ch >> ch >> vx >> ch >> vy;
		getline(input, line);
		
		xpos += 100 * vx;
		xpos %= WIDTH;
		if (xpos < 0) xpos += WIDTH;
		ypos += 100 * vy;
		ypos %= HEIGHT;
		if (ypos < 0) ypos += HEIGHT;
		m[point(xpos, ypos)]++;
	}

	int a = 0, b = 0, c = 0, d = 0;
	for (int i = 0; i < WIDTH / 2; i++)
		for (int j = 0; j < HEIGHT / 2; j++)
			a += m[point(i, j)];
	for (int i = WIDTH / 2 + 1; i < WIDTH; i++)
		for (int j = 0; j < HEIGHT / 2; j++)
			b += m[point(i, j)];
	for (int i = 0; i < WIDTH / 2; i++)
		for (int j = HEIGHT / 2 + 1; j < HEIGHT; j++)
			c += m[point(i, j)];
	for (int i = WIDTH / 2 + 1; i < WIDTH; i++)
		for (int j = HEIGHT / 2 + 1; j < HEIGHT; j++)
			d += m[point(i, j)];

	cout << a << ", " << b << ", " << c << ", " << d << ", " << a * b*c*d << endl;

}

