// week5_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
using namespace std;

set<pair<int, int>> rules;

bool check(const vector<int>& v) {
	for (int i = 0; i < v.size(); i++)
		for (int j = i + 1; j < v.size(); j++)
			if (rules.count(pair<int, int>(v[i], v[j])) == 0)
				return false;
	return true;
}

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}
	string line;
	while (true) {
		getline(input, line);
		if (line.size() == 0)
			break;
		stringstream ss(line);
		int nr1, nr2;
		char ch;
		ss >> nr1 >> ch >> nr2;
		rules.insert(pair<int, int>(nr1, nr2));
	}
	int sum = 0;
	while (getline(input, line)) {
		stringstream ss(line);
		vector<int> v;
		while (ss) {
			int i;
			char ch;
			ss >> i;
			v.push_back(i);
			ss >> ch;		
		}	
		if (check(v)) {
			sum += v[v.size() / 2];
		}
	}
	cout << sum << endl;
	return 0;
}

