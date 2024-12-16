
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <set>
#include "../../adventofcode2023/matrix_new/matrix.h"
using namespace std;



int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	matrix<char> m;
	input >> m;

	int xpos = 0, ypos = 0;
	for(int i = 0; i < m.getRows(); i++)
		for(int j = 0; j < m.getCols(); j++)
			if (m[i][j] == '@') {
				xpos = i;
				ypos = j;
			}
	
	char ch;
	while (input >> ch){
		//cout << m << endl;
		//cout << "Move " << ch << ":" << endl;
		
		if (ch == '^') {
			if (m[ypos - 1][xpos] == '#')
				continue;
			if (m[ypos - 1][xpos] == '.') {
				m[ypos][xpos] = '.';
				ypos--;
				m[ypos][xpos] = '@';
				continue;
			}
			if (m[ypos - 1][xpos] == 'O') {
				int i = ypos - 1;
				while (m[i][xpos] == 'O')
					i--;
				if (m[i][xpos] == '#')
					continue;
				if (m[i][xpos] == '.') {
					while (i < ypos) {
						m[i][xpos] = 'O';
						i++;
					}
					m[ypos][xpos] = '.';
					ypos--;
					m[ypos][xpos] = '@';

				}
				continue;
			}
		}
		if (ch == 'v') {
			if (m[ypos + 1][xpos] == '#')
				continue;
			if (m[ypos + 1][xpos] == '.') {
				m[ypos][xpos] = '.';
				ypos++;
				m[ypos][xpos] = '@';
				continue;
			}
			if (m[ypos + 1][xpos] == 'O') {
				int i = ypos + 1;
				while (m[i][xpos] == 'O')
					i++;
				if (m[i][xpos] == '#')
					continue;
				if (m[i][xpos] == '.') {
					while (i > ypos) {
						m[i][xpos] = 'O';
						i--;
					}
					m[ypos][xpos] = '.';
					ypos++;
					m[ypos][xpos] = '@';

				}
				continue;
			}
		}
		if (ch == '>') {
			if (m[ypos ][xpos + 1] == '#')
				continue;
			if (m[ypos][xpos + 1 ] == '.') {
				m[ypos][xpos] = '.';
				xpos++;
				m[ypos][xpos] = '@';
				continue;
			}
			if (m[ypos ][xpos + 1] == 'O') {
				int i = xpos + 1;
				while (m[ypos][i] == 'O')
					i++;
				if (m[ypos][i] == '#')
					continue;
				if (m[ypos][i] == '.') {
					while (i > xpos) {
						m[ypos][i] = 'O';
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
			if (m[ypos][xpos - 1] == 'O') {
				int i = xpos - 1;
				while (m[ypos][i] == 'O')
					i--;
				if (m[ypos][i] == '#')
					continue;
				if (m[ypos][i] == '.') {
					while (i < xpos) {
						m[ypos][i] = 'O';
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
	cout << m << endl;
	int sum = 0;
	for (int i = 0; i < m.getCols(); i++)
		for (int j = 0; j < m.getRows(); j++)
			if(m[i][j] == 'O')
				sum += 100*i + j;
	cout << sum << endl;



	


}

