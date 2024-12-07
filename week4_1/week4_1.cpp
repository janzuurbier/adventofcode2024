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
	if (m[i][j] == s[0])
	{
		bool b = true;
		for (int k = 0; k < s.size() && b; k++)
			if (!m.isInRange(i + k, j) || m[i + k][j] != s[k])
				b = false;
		if (b)
			retval++;
		b = true;
		for (int k = 0; k < s.size() && b; k++)
			if (!m.isInRange(i - k, j) || m[i - k][j] != s[k])
				b = false;
		if (b)
			retval++;
		b = true;
		for (int k = 0; k < s.size() && b; k++)
			if (!m.isInRange(i, j + k) || m[i][j + k] != s[k])
				b = false;
		if (b)
			retval++;
		b = true;
		for (int k = 0; k < s.size() && b; k++)
			if (!m.isInRange(i, j - k) || m[i][j - k] != s[k])
				b = false;
		if (b)
			retval++;
		b = true;
		for (int k = 0; k < s.size() && b; k++)
			if (!m.isInRange(i + k, j + k) || m[i + k][j + k] != s[k])
				b = false;
		if (b)
			retval++;
		b = true;
		for (int k = 0; k < s.size() && b; k++)
			if (!m.isInRange(i + k, j - k) || m[i + k][j - k] != s[k])
				b = false;
		if (b)
			retval++;
		b = true;
		for (int k = 0; k < s.size() && b; k++)
			if (!m.isInRange(i - k, j + k) || m[i - k][j + k] != s[k])
				b = false;
		if (b)
			retval++;
		b = true;
		for (int k = 0; k < s.size() && b; k++)
			if (!m.isInRange(i - k, j - k) || m[i - k][j - k] != s[k])
				b = false;
		if (b)
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
			//cout << i << ", " << j << ": " << nr_xmas(word_search, i, j) << endl;
		}
	cout << count << endl;
}

