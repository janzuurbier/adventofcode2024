// week7_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

uint64_t concat(uint64_t a, uint64_t b) {
	string s = to_string(a);
	string t = to_string(b);
	return stoull(s + t);
}

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	string line;
	int64_t sum = 0;
	while (getline(input, line)) {
		stringstream ss(line);
		uint64_t value;
		ss >> value;
		char ch;
		int getal;
		ss >> ch;
		ss >> getal;
		set<uint64_t> v;
		v.insert(getal);
		while (ss >> getal) {
			set<uint64_t> w;
			for (uint64_t i : v) {
				if (i + getal <= value) w.insert(i + getal);
				if (i * getal <= value) w.insert(i * getal);
				uint64_t temp = concat(i, getal);
				if (temp <= value) w.insert(temp);
			}
			v = w;
		}

		for (uint64_t i : v) {
			if (i == value)
				sum += value;
		}
	}
	cout << sum << endl;
}

