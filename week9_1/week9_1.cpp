// week9_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
	int endpos = 0;
	for (int i = 0; i < blocks.size(); i++)
		endpos += blocks[i];
	vector<bool> removed;
	for(int i = 0; pos < endpos ; i++) {
		
			for (int j = 0; j < blocks[i] && pos < endpos; j++) {
				checksum += pos * i;
				pos++;
			}
			for (int j = 0; j < spaces[i] && pos < endpos; j++) {
				if (blocks.back() == 0)
					blocks.pop_back();
				checksum += pos * (blocks.size() - 1);
				blocks.back()--;
				pos++;
			}
		
		
	}
	cout << checksum << endl;

}

