#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <stdlib.h>
#include <list>
#include <time.h>
#include <set>
using namespace std;

map<string, bool> value_of;

enum operation_t { OR, AND, XOR };

struct gate {
	string input1;
	string input2;
	operation_t operation;
	string output;

	gate(string i1, string i2, operation_t op, string out) :
		input1(i1), input2(i2), operation(op), output(out) {}

	gate() {}

	friend bool operator==(const gate& a, const gate& b) {
		return
			(a.input1 == b.input1) &&
			(a.input2 == b.input2) &&
			(a.operation == b.operation) &&
			(a.output == b.output);
	}

	bool get_output() {
		switch (operation) {
		case OR: return value_of[input1] || value_of[input2];
		case AND: return value_of[input1] && value_of[input2];
		case XOR: return value_of[input1] ^ value_of[input2];
		}
	}

	bool input_complete() {
		return value_of.count(input1) > 0 && value_of.count(input2) > 0;
	}

	string to_string() {
		string s = "";
		switch (operation) {
		case OR: s = "OR"; break;
		case AND: s = "AND"; break;
		case XOR: s = "XOR";
		}
		return input1 + " " + s + " " + input2 + " -> " + output;
	}
};

string to_binary_string(uint64_t i, int size) {
	if (i == 0)
		return "0";
	string s = "";
	int pos = 0;
	while (i > 0) {
		int digit = i & 1;
		i >>= 1;
		string t = to_string(digit);
		if (pos % 5 == 0)
			t += " ";
		s = t + s;	
		pos++;
	}
	for (int k = pos; k <= size; k++) {
		if (k  % 5 == 0)
			s =  " " + s;
		s = "0" + s;
	}
		
	return s;
}

list<gate> gates;
map<string, gate> gate_with_output;

map<string, int> m;

void sub_count_pred(ostream& out, string output) {
	if (gate_with_output.count(output) > 0) {
		gate g = gate_with_output[output];
		if (g.input1[0] == 'x')
			if (m.count(g.input1) == 0)
				m[g.input1] = 1;
			else
				m[g.input1] = m[g.input1] + 1;
		else
			sub_count_pred(out, g.input1);
		if (g.input2[0] == 'x' )
			if (m.count(g.input2) == 0)
				m[g.input2] = 1;
			else
				m[g.input2] = m[g.input2] + 1;
		else
			sub_count_pred(out, g.input2);
	}
}

void count_pred(ostream& out, string output) {
	m.clear();
	sub_count_pred(out, output);
	for (auto it = m.begin(); it != m.end(); it++)
		out << it->first << "(" << it->second << ") ";
}

void print_tree(ostream& out, string output, int level = 0) {
	if (gate_with_output.count(output) > 0) {
		gate g = gate_with_output[output];
		for (int i = 0; i < level; i++)
			out << ".";
		out << g.to_string() << endl;
		print_tree(out, g.input1,level + 1);
		print_tree(out, g.input2, level + 1);
	}
}

vector < pair<string, string>> swaps;


int main()
{
	srand(time(NULL));

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
		value_of[s] = false;
	}
	for (auto it = value_of.begin(); it != value_of.end(); it++) {
		int r1 = rand()%2;
		if (it->first[0] == 'x' && r1 == 1)
			it->second = true;
		if (it->first[0] == 'y' && r1 == 1)
			it->second = true;
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

	swaps.push_back(pair<string, string>("z11", "wpd"));
	swaps.push_back(pair<string, string>("jqf", "skh"));
	swaps.push_back(pair<string, string>("z19", "mdd"));
	swaps.push_back(pair<string, string>("z37", "wts"));


	for (gate& g : gates) {
		for (pair<string, string> p : swaps) {
			if (g.output == p.first)
				g.output = p.second;
			else if (g.output == p.second)
				g.output = p.first;
		}
		gate_with_output[g.output] = g;
	}

	

	while (!gates.empty()) {
		for (auto it = gates.begin(); it != gates.end(); ) {
			if (it->input_complete()) {
				value_of[it->output] = it->get_output();
				it = gates.erase(it);
			}
			else
				it++;
		}
	}

	uint64_t ix = 0;
	uint64_t iy = 0;
	uint64_t iz = 0;
	for (auto it = prev(value_of.end()); ; it--) {
		if (it->first[0] == 'x') {
			ix <<= 1;
			if (it->second)
				ix += 1;
		}
		if (it->first[0] == 'y') {
			iy <<= 1;
			if (it->second)
				iy += 1;
		}
		if (it->first[0] == 'z') {
			iz <<= 1;
			if (it->second)
				iz += 1;
		}
		if (it == value_of.begin())
			break;
	
	}
	cout <<  to_binary_string(ix, 45) << endl;
	cout <<  to_binary_string(iy, 45) << endl;
	cout << to_binary_string(iz, 45) << endl;
	cout << to_binary_string(ix + iy, 45) << endl;

	ofstream out("C:\\Users\\Jan\\Desktop\\output.txt");
	for (int i = 0; i < 10; i++) {
		print_tree(out, "z0" + to_string(i));
		out << endl;
	}
	for (int i = 10; i <= 45; i++) {
		print_tree(out, "z" + to_string(i));
		out << endl;
	}

	set<string> final;
	for (pair<string, string> p : swaps) {
		final.insert(p.first);
		final.insert(p.second);
	}
	for (string s : final) 
		cout << s << ",";
	cout << endl;


	

	
	

	

	
	
	
	
	



}

