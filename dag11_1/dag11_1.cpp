// dag11_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <set>
using namespace std;

map<string, uint64_t> lookup;

pair<string, string>transform(string s) {
	if (s == "0") 
		return pair<string, string> ("1", "");
	else if (s.size() % 2 == 0) {
		string left = s.substr(0, s.size() / 2);
		string right = s.substr(s.size() / 2, s.size() / 2);
		while (right.size() > 1 && right[0] == '0') {
			right = right.substr(1);
		}
		return pair<string, string>(left, right);
	}
	else {
		uint64_t i = stoll(s);
		i *= 2024;
		string t = to_string(i);
		return pair<string, string>(t, "");
	}	
}

uint64_t nr_transforms(string s, int aantal) {
	if (aantal > 0) {
		pair<string, string> p = transform(s);
		
		if (p.second.size() == 0) {
			return nr_transforms(p.first, aantal - 1);
		}
		else {
			return nr_transforms(p.first, aantal - 1) + nr_transforms(p.second, aantal - 1);
		}
			
	}
	else
		return 1;
}

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}
	string s;
	int sum = 0;
	while (input >> s) {
		sum += nr_transforms(s, 25);
	}
	cout << sum << endl;	
}

