
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
using namespace std;

int64_t A, B, C;
int pointer = 0;

int combo(int x) {
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
	x = combo(x);
	x %= 8;
	if (x < 0) x += 8;
	B = x;
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
	x = combo(x);
	x %= 8;
	if (x < 0) x += 8;
	cout <<x << ",";
}

void bdv(int x) {
	B = A >> combo(x);
}

void cdv(int x) {
	C = A >> combo(x);
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
	getline(input, line);
	line = line.substr(12);
	B = stoi(line);
	getline(input, line);
	line = line.substr(12);
	C = stoi(line);

	//cout << A << " " << B << " " << C << endl << endl;
	
	vector<int> program;
	getline(input, line);
	input >> line;
	while (input) {
		int i;
		char ch;
		input >> i >> ch;
		program.push_back(i);
	}
		
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
	//cout << "klaar" << endl;
		
	
}

