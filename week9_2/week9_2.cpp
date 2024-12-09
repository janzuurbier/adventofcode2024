// week9_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}
	char ch;
	vector<int> blocks;
	vector<int> spaces;
	while (true) {
		if (input >> ch) {
			int a = ch - 48;
			blocks.push_back(a);
		}
		else break;
		if (input >> ch) {
			int b = ch - 48;
			spaces.push_back(b);
		}
		else break;
	}
	uint64_t checksum = 0;
	int pos = 0; 
	
	vector<bool> moved;
	for (int i = 0; i < blocks.size(); i++)
		moved.push_back(false);
	
	for(int i = 0;  ; i++) {
		if (!moved[i]) {
			for (int j = 0; j < blocks[i] ; j++) {
				checksum += pos * i;
				pos++;
			}
			moved[i] = true;
		}
		else {
			pos += blocks[i];
		}


		if (i == spaces.size())
			break;

		int k = blocks.size() - 1;
		while (spaces[i] > 0) {
			while (blocks[k] > spaces[i] || moved[k]) {
				k--;
				if (k <= i)
					break;
			}
			if (k <= i)
				break;
			for (int j = 0; j < blocks[k]; j++) {
				checksum += pos * k;
				pos++;
			}
			moved[k] = true;
			spaces[i] -= blocks[k];
		}
		pos += spaces[i];
	}
	cout << checksum << endl;

}

