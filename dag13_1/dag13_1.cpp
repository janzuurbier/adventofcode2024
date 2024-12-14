
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <set>
using namespace std;

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	uint64_t total_cost = 0;
	while (input) {
		string line;
		int a, b, c, d;
		int64_t e, f;
		char ch;
		input >> ch;
		while (ch != '+') input >> ch;
		input >> a;
		input >> ch;
		while (ch != '+') input >> ch;
		input >> b;
		getline(input, line);
		input >> ch;
		while (ch != '+') input >> ch;
		input >> c;
		input >> ch;
		while (ch != '+') input >> ch;
		input >> d;
		getline(input, line);
		input >> ch;
		while (ch != '=') input >> ch;
		input >> e;
		e += 10000000000000L;//part 2
		input >> ch;
		while (ch != '=') input >> ch;
		input >> f;
		f += 10000000000000L;//part 2
		getline(input, line); 
		getline(input, line);

		cout  << a << ", " << b << ", " << c << ", " << d << ", " << e << ", " << f << endl;
		
		int det = a * d - b * c;
		if (det == 0) {
			cout << "det = 0: " << a << ", " << b << ", " << c << ", " << d << endl;
		}
		else {
			int64_t x = d * e - c * f;
			int64_t y = -b * e + a * f;
			if (x % det == 0 && y % det == 0 ) {
				x /= det;
				y /= det;
				cout << x  << ", " << y  << " ";
				cout << "kosten " << 3 * x + y << endl;
				total_cost += 3 * x + y;
			}
			else
				cout << "geen oplossing" << endl;
			
		}


	}
	cout << total_cost << endl;
}

