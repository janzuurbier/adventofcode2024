// week4_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "../../adventofcode2023/matrix_new/matrix.h"
using namespace std;

int nr_xmas(matrix<char>& m, int i, int j) {

	int retval = 0;
	string s = "XMAS";
	if (m[i][j] == 'A')
	{
		if (
			m.isInRange(i - 1, j - 1) && m[i - 1][j - 1] == 'M' && 
			m.isInRange(i + 1, j + 1) && m[i+1][j+1] == 'S' && 
			m.isInRange(i - 1, j + 1) && m[i-1][j + 1] == 'M' &&
			m.isInRange(i + 1, j - 1) && m[i+1][j - 1] == 'S'
		)
		retval++;
		if (
			m.isInRange(i - 1, j - 1) && m[i - 1][j - 1] == 'M' &&
			m.isInRange(i + 1, j + 1) && m[i + 1][j + 1] == 'S' &&
			m.isInRange(i - 1, j + 1) && m[i - 1][j + 1] == 'S' &&
			m.isInRange(i + 1, j - 1) && m[i + 1][j - 1] == 'M'
		)
		retval++;
		if (
			m.isInRange(i - 1, j - 1) && m[i - 1][j - 1] == 'S' &&
			m.isInRange(i + 1, j + 1) && m[i + 1][j + 1] == 'M' &&
			m.isInRange(i - 1, j + 1) && m[i - 1][j + 1] == 'M' &&
			m.isInRange(i + 1, j - 1) && m[i + 1][j - 1] == 'S'
		)
		retval++;
		if (
			m.isInRange(i - 1, j - 1) && m[i - 1][j - 1] == 'S' &&
			m.isInRange(i + 1, j + 1) && m[i + 1][j + 1] == 'M' &&
			m.isInRange(i - 1, j + 1) && m[i - 1][j + 1] == 'S' &&
			m.isInRange(i + 1, j - 1) && m[i + 1][j - 1] == 'M'
		)
		retval++;
		

	}
	return retval;
}

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}
	matrix<char> word_search;
	input >> word_search;

	int count = 0;
	for (int i = 0; i < word_search.getCols(); i++)
		for (int j = 0; j < word_search.getRows(); j++) {
			count += nr_xmas(word_search, i, j);
		}
	cout << count << endl;
}

