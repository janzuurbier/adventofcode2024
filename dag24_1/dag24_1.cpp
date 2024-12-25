#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <set>
#include <list>
#include "../../adventofcode2023/matrix_new/matrix.h"
using namespace std;

map<string, bool> value;

enum operation_t { OR, AND, XOR };

struct gate {
	string input1;
	string input2;
	operation_t operation;
	string output;

	gate(string i1, string i2, operation_t op, string out) :
		input1(i1), input2(i2), operation(op), output(out) {}

	bool get_output() {
		switch (operation) {
		case OR: return value[input1] || value[input2];
		case AND: return value[input1] && value[input2];
		case XOR: return value[input1] ^ value[input2];
		}
	}

	bool input_complete() {
		return value.count(input1) > 0 && value.count(input2) > 0;
	}

	string to_string() {
		string s = "";
		switch (operation) {
		case OR: s = "OR";
		case AND: s = "AND";
		case XOR: s = "XOR";
		}
		return input1 + " " + s + " " + input2  + " -> " + output;
	}
};

list<gate> gates;


int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}
	string line;
	while (getline(input, line)) {
		if (line.size() == 0)
			break;
		stringstream ss(line);
		string s;
		bool b;
		ss >> s >> b;
		s = s.substr(0, s.size() - 1);
		value[s] = b;	
	}

	while (getline(input, line)) {
		stringstream ss(line);
		string s1, s2, s3, s4;
		string dummy;
		ss >> s1 >> s2 >> s3 >> dummy >> s4;
		operation_t op;
		if (s2 == "OR")
			op = OR;
		else if (s2 == "AND")
			op = AND;
		else
			op = XOR;
		gate g(s1, s3, op, s4);
		gates.push_back(g);
	}

	while (!gates.empty()) {
		for (auto it = gates.begin(); it != gates.end(); ) {
			if (it->input_complete()) {
				value[it->output] = it->get_output();
				it = gates.erase(it);
			}
			else
				it++;
		}
	}

	/*for (auto it = value.begin(); it != value.end(); it++) {
		cout << it->first << ": " << it->second << endl;
	}*/

	uint64_t i = 0;
	for (auto it = prev(value.end()); it->first[0] == 'z'; it--) {
		cout << it->second;
		i <<= 1;
		if (it->second)
			i += 1;
	}
	cout << endl;
	cout << i << endl;


}

