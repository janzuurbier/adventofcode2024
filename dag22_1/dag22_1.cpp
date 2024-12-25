
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <set>
#include <queue>
using namespace std;

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
	uint64_t sum = 0;
	while (input >> n) {
		cout << n << ": ";
		for (int i = 0; i < 2000; i++)
			evolve(n);
		cout << n << endl;
		sum += n;
	}
	cout << sum << endl;

}

