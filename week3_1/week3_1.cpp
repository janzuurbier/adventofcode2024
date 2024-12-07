// week3_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}
	long retval = 0;
	string line;
	string program = "";
	while (getline(input, line)) {
		program += line;
	}
	size_t pos = 0;
	while (true) {
		pos = program.find( "mul(", pos);
		if (pos == string::npos)
			break;
		pos += 4;
		char ch = program[pos];
		string s = "";
		int left, right;
		while (ch >= '0' && ch <= '9') {
			pos++;
			s += ch;
			ch = program[pos];
		}
		if (1 <= s.size() && s.size() <= 3) {
			left = stoi(s);
		}
		else
			continue;
		if (program[pos] == ',')
			pos++;
		else
			continue;
		s = "";
		ch = program[pos];
		while (ch >= '0' && ch <= '9') {
			pos++;
			s += ch;
			ch = program[pos];
		}
		if (1 <= s.size() && s.size() <= 3) {
			right = stoi(s);
		}
		else
			continue;
		if (program[pos] == ')')
			pos++;
		else
			continue;
		retval += left * right;
	}
	cout << retval << endl;

}

