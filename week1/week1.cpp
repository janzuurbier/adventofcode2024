// week1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
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
	int sum = 0;
	for (int i = 0; i < aantal; i++) {
		//cout << links[i] << ", " << rechts[i];
		int verschil = abs(rechts[i] - links[i]);
		sum += verschil;
		//cout << "\t" << verschil << endl;

	}
	cout << sum << endl;

}

