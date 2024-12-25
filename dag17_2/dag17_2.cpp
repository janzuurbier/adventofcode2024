
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <set>
#include <iomanip>
#include "../../adventofcode2023/matrix_new/matrix.h"
using namespace std;

uint64_t A, B, C, AA, BB, CC;
int pointer = 0;
vector<int> program;
string s;

uint64_t combo(int x) {
	if (0 <= x && x <= 3)
		return x;
	if (x == 4)
		return A;
	if (x == 5)
		return B;
	if (x == 6)
		return C;
	cout << "fout argument voor combo: " << x << endl;
	return 0;
}

void adv(int x) {
	A >>= combo(x);
}

void bxl(int x) {
	B ^= x;
}

void bst(int x) {
	uint64_t y = combo(x);
	y %= 8;
	if (y < 0) y += 8;
	B = y;
}

bool jnz(int x) {
	if (A != 0) {
		pointer = x;
		return false;
	}
	else
		return true;
}

void bcx(int x) {
	B ^= C;
}

void out(int x) {
	uint64_t y = combo(x);
	y %= 8;
	if (y < 0) y += 8;
	s = s + to_string(y) + ",";
}

void bdv(int x) {
	B = A >> combo(x);
}

void cdv(int x) {
	C = A >> combo(x);
}

string run_program(int64_t AAA) {
	A = AAA;
	B = BB;
	C = CC;
	pointer = 0;
	s = "";
	while (pointer < program.size()) {
		int instruction = program[pointer];
		int operand = program[pointer + 1];
		switch (instruction) {
		case 0:
			adv(operand);
			pointer += 2;
			break;
		case 1:
			bxl(operand);
			pointer += 2;
			break;
		case 2:
			bst(operand);
			pointer += 2;
			break;
		case 3:
			if (jnz(operand))
				pointer += 2;
			break;
		case 4:
			bcx(operand);
			pointer += 2;
			break;
		case 5:
			out(operand);
			pointer += 2;
			break;
		case 6:
			bdv(operand);
			pointer += 2;
			break;
		case 7:
			cdv(operand);
			pointer += 2;
			break;
		}
		
	}
	return s;
}



int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	string line;
	getline(input, line);
	line = line.substr(12);
	A = stoll(line);
	AA = A;
	getline(input, line);
	line = line.substr(12);
	B = stoi(line);
	BB = B;
	getline(input, line);
	line = line.substr(12);
	C = stoi(line);
	CC = C;

	getline(input, line);
	input >> line;
	while (input) {
		int i;
		char ch;
		input >> i >> ch;
		program.push_back(i);
	}

	string t = "";
	for (int i = 0; i < program.size(); i++)
		t = t + to_string(program[i]) + ",";
	vector<uint64_t> v;
	v.push_back(0);
	vector<uint64_t> w;
	for(int k = 1; k < program.size() + 1; k++){
		for (int i = 0; i < 8; i++) {
			for (uint64_t j : v) {
				run_program(j * 8 + i);
				if (s == t.substr(t.size() - 2 * k))
					w.push_back(j * 8 + i);
			}
		}
		v = w;
		w.clear();
	}
	sort(v.begin(), v.end());
	for (int64_t i : v)
		cout << i << endl;

}
/*
	string t = "2,4,1,2,7,5,4,1,1,3,5,5,0,3,3,0,";
	int rij[] = { 17, 81, 86, 94, 135, 143, 145, 151, 159, 209, 214, 222, 273, 
		337, 342, 350, 391, 399, 401, 407, 415, 452, 460, 465, 468, 470, 476, 
		478, 484, 492, 500, 508 };
	set<uint64_t> v;
	for(int i : rij)
		v.insert(i);

	set<int64_t> w;
	
	int d = 512;
	for(int k = 0; k < 15; k++) {
		for (uint64_t i : v) {
			for (int j = 0; j < 8; j++) {
				A = (512 << (3 * k))*j + i;
				C = CC;
				pointer = 0;
				s = "";
				while (pointer < program.size()) {
					int instruction = program[pointer];
					int operand = program[pointer + 1];
					switch (instruction) {
					case 0:
						adv(operand);
						pointer += 2;
						break;
					case 1:
						bxl(operand);
						pointer += 2;
						break;
					case 2:
						bst(operand);
						pointer += 2;
						break;
					case 3:
						if (jnz(operand))
							pointer += 2;
						break;
					case 4:
						bcx(operand);
						pointer += 2;
						break;
					case 5:
						out(operand);
						pointer += 2;
						break;
					case 6:
						bdv(operand);
						pointer += 2;
						break;
					case 7:
						cdv(operand);
						pointer += 2;
						break;
					}


					
				}
				if (s.substr(0, 2 * k + 1) == t.substr(0, 2 * k + 1))
					w.insert((512 << (3 * k))*j + i);
				if (s == t)
					cout << ((512 << (3 * k))*j + i) << endl;

			}
		}
		
			
		
		v.clear();
		for (uint64_t i : w)
			v.insert(i);
		w.clear();
		
	}
	//cout << "klaar" << endl;

}*/

