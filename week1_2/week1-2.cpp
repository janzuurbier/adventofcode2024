// week1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int count(vector<int> v, int n, int start = 0) {
	int aantal = 0;
	for (int i = start; i < v.size(); i++) {
		if (v[i] == n)
			aantal++;
		else if (v[i] > n)
			break;
	}
	return aantal;
}

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}
	vector<int> links, rechts;
	int aantal = 0;
	int x, y;
	while (input >> x >> y) {
		aantal++;
		links.push_back(x);
		rechts.push_back(y);
	}
	cout << aantal << endl;
	sort(links.begin(), links.end());
	sort(rechts.begin(), rechts.end());
	int score = 0;
	int i = 0, j = 0;
	for (int i = 0; i < aantal; i++) {
		int c = count(rechts, links[i]);
		int s = c * links[i];
		cout << c <<  ", " << s << endl;
		score += s;
	}
	cout << score << endl;

}

