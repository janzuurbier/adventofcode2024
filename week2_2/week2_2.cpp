// week2_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int nr_increases(const vector<int>& v) {
	int nr = 0;
	for (int i = 1; i < v.size(); i++) {
		if (v[i - 1] < v[i])
			nr++;
	}
	return nr;
}

int nr_decreases(const vector<int>& v) {
	int nr = 0;
	for (int i = 1; i < v.size(); i++) {
		if (v[i - 1] > v[i])
			nr++;
	}
	return nr;
}

bool has_big_steps(const vector<int>& v){
	int nr = 0;
	for (int i = 1; i < v.size(); i++) {
		if (abs(v[i - 1] - v[i]) > 3)
			return true;
	}
	return false;
}


int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}
	string line;
	int nrSafe = 0;
	int nrLines = 0;
	
	while (getline(input, line)) {
		nrLines++;
		stringstream report(line);
		int level;
		vector<int> v;
		while (report >> level)
			v.push_back(level);
		bool safe = false;
		if ((nr_increases(v) == v.size()-1 || nr_decreases(v) == v.size() - 1) && !has_big_steps(v)) {
			nrSafe++;
			safe = true;
		}
		for (int i = 0; i < v.size()&& !safe ; i++) {
			vector<int> w;
			for (int j = 0; j < v.size(); j++)
				if (j != i) w.push_back(v[j]);
			if ((nr_increases(w) == w.size() - 1 || nr_decreases(w) == w.size() - 1) && !has_big_steps(w)) {
				nrSafe++;
				safe = true;
			}
		}
	}
	cout << nrLines << endl << nrSafe << endl;

}

