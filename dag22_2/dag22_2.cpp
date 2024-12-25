// dag22_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <set>
#include <queue>
using namespace std;

typedef int sequence;

//save memory 4*4 bytes -> 1*4 byte.
int to_sequence(int a, int b, int c, int d) {
	int retval = a + 10;
	retval = retval * 20 + b + 10;
	retval = retval * 20 + c + 10;
	retval = retval * 20 + d + 10;
	return retval;
}

string tostring(sequence s) {
	int a = s % 20 - 10;
	s /= 20;
	int b = s % 20 - 10;
	s /= 20;
	int c = s % 20 - 10;
	s /= 20;
	int d = s - 10;
	return to_string(a) + "," + to_string(b) + ","
		+ to_string(c) + "," + to_string(d);
}

map<sequence, vector<int>> number_map;
map<pair<sequence, int>, int> banana_map;
vector<int> intitial_secret_numbers;

int mix(int& secret_number, int x) {
	secret_number ^= x;
	return secret_number;
}

int prune(int& secret_number) {
	secret_number &= 0xffffff;
	return secret_number;
}

int evolve(int& secret_number) {
	int result = secret_number << 6;
	mix(secret_number, result);
	prune(secret_number);
	result = secret_number >> 5;
	mix(secret_number, result);
	prune(secret_number);
	result = secret_number << 11;
	mix(secret_number, result);
	prune(secret_number);
	return secret_number;
}

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}
	
	int n;
	while (input >> n) {
		intitial_secret_numbers.push_back(n);
	}

	for(int secret_number : intitial_secret_numbers){
		deque<int> last_4_changes;
		int old_n = secret_number % 10;
		set<sequence> sequences;
		for (int j = 0; j < 4; j++) {
			evolve(secret_number);
			int n = secret_number % 10;
			int change = n - old_n;
			last_4_changes.push_back(change);
			old_n = n;
		}
		for (int j = 4; j < 2000; j++) {
			evolve(secret_number);
			int n = secret_number % 10;
			int change = n - old_n;
			last_4_changes.push_back(change);
			last_4_changes.pop_front();
			old_n = n;
			sequence seq = to_sequence(last_4_changes[0], last_4_changes[1], 
				last_4_changes[2], last_4_changes[3]);
			if (n > 0  && sequences.count(seq) == 0) {
					sequences.insert(seq);
					number_map[seq].push_back(secret_number);
					banana_map[pair<sequence, int>(seq, secret_number)] = n;
			}
		}
	}
	int max = 0;
	for(auto it = number_map.begin(); it != number_map.end(); it++){
		int sum = 0;
		for (int b : it->second) {
			sum += banana_map[pair<sequence, int>(it->first, b)];	
		}
		if (sum > max)
			max = sum;
	}
	cout << max << endl;
}

