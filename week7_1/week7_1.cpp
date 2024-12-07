// week7_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

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
		//cout << value;
		char ch;
		int getal;
		ss >> ch;
		ss >> getal;
		set<uint64_t> v;
		v.insert(getal);
		while (ss >> getal) {
			set<uint64_t> w;
			for (uint64_t i : v) {
				w.insert(i + getal);
				w.insert(i * getal);
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

