// week3_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
	string program_with_dos_and_donts = "";
	while (getline(input, line)) {
		program_with_dos_and_donts += line;
	}
	size_t pos1 = 0;
	size_t pos2 = 0;
	string program = "";
	while (true) {
		pos1 = program_with_dos_and_donts.find("don't()", pos2);
		if (pos1 == string::npos) {
			program += program_with_dos_and_donts.substr(pos2);
			break;
		}
		else {
			program += program_with_dos_and_donts.substr(pos2, pos1 - pos2);
			pos2 = program_with_dos_and_donts.find("do()", pos1);
			if (pos2 == string::npos)
				break;
		}
	}
	size_t pos = 0;
	while (true) {
		pos = program.find("mul(", pos);
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

