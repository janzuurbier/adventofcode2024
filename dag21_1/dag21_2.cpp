#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include "../../adventofcode2023/matrix_new/matrix.h"
using namespace std;

typedef pair<char, char> transition;
map<transition, string> m;

string calc(string s ) {
	s = "A" + s;
	string t = "";
	for (int i = 0; i < s.size() - 1; i++)
		t += m[transition(s[i], s[i + 1])];
	return t;
}

int main()
{
	//A komt altijd achter aan. Dit zorgt voor de druk op de knop
	//Als de robotarm is gepositioneerd.
	//Zoveel mogelijk dezelfde bewegingen direct achter elkaar.
	//Verder voorkeur <^ boven ^<, v> boven >v, <v boven v<. Dit zorgt
	//kortere strings voor de vervolg robots.
	//Zorg wel dat de arm niet boven de lege vakjes komt.
	m[transition('A', 'A')] = "A";
	m[transition('A', 'v')] = "<vA";
	m[transition('A', '^')] = "<A";
	m[transition('A', '>')] = "vA";
	m[transition('A', '<')] = "v<<A";
	m[transition('^', 'A')] = ">A";
	m[transition('^', '^')] = "A";
	m[transition('^', 'v')] = "vA";
	m[transition('^', '>')] = "v>A";
	m[transition('^', '<')] = "v<A";
	m[transition('v', 'A')] = "^>A";
	m[transition('v', '^')] = "^A";
	m[transition('v', 'v')] = "A";
	m[transition('v', '>')] = ">A";
	m[transition('v', '<')] = "<A";
	m[transition('>', 'A')] = "^A";
	m[transition('>', '^')] = "<^A";
	m[transition('>', 'v')] = "<A";
	m[transition('>', '>')] = "A";
	m[transition('>', '<')] = "<<A";
	m[transition('<', 'A')] = ">>^A";
	m[transition('<', '^')] = ">^A";
	m[transition('<', 'v')] = ">A";
	m[transition('<', '>')] = ">>A";
	m[transition('<', '<')] = "A";
	
	//x12 is om de tranisitiestrings 12 stappen vooruit te berekenen.
	map<string, string> x12;
	//Met x12 kan je x24 berekenen, 24 stappen vooruit. 
	//Niet de hele string maar alleen de lengte is van belang. 
	map<string, uint64_t> x24;
	
	char tekens[] = { '^', 'v', '>', '<', 'A' };
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++) {
			string s = m[transition(tekens[i],tekens[j])];
			string t = s;
			for (int i = 0; i < 12; i++) {
				s = calc(s);
			}
			x12[t] = s;	
		}
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++) {
			string s = m[transition(tekens[i], tekens[j])];
			string temp = x12[s];
			x24[s] = 0;
			while (temp.size() > 0) {
				size_t pos = temp.find_first_of('A');
				string u = temp.substr(0, pos + 1);
				temp = temp.substr(pos + 1);
				x24[s] += x12[u].size();
			}
		}

	uint64_t sum = 0;
	int code = 839;
	string s = calc("<^^^Avv>A^^AvvvA");
	//int code = 29;
	//string s = calc("<A^A^^>AvvvA");
	uint64_t val = 0;
	while(s.size() > 0) {
		size_t pos = s.find_first_of('A');
		string u = s.substr(0, pos + 1);
		s = s.substr(pos + 1);
		val += x24[u];
	}
	sum += val * code;
	code  = 169;
	s = calc("^<<A^>>A^AvvvA");
	//code = 980;
	//s = calc("^^^A>AvvvA>A");
	val = 0;
	while (s.size() > 0) {
		size_t pos = s.find_first_of('A');
		string u = s.substr(0, pos + 1);
		s = s.substr(pos + 1);
		val += x24[u];
	}
	sum += val * code;
	code = 579;
	s = calc("<^^A<^A>>AvvvA");
	//code = 179;
	//s = calc("^<<A^^A>>AvvvA");
	val = 0;
	while (s.size() > 0) {
		size_t pos = s.find_first_of('A');
		string u = s.substr(0, pos + 1);
		s = s.substr(pos + 1);
		val += x24[u];
	}
	sum += val * code;
	code = 670;
	s = calc("^^A<<^A>vvvA>A");
	//code = 456;
	//s = calc("^^<<A>A>AvvA");
	val = 0;
	while (s.size() > 0) {
		size_t pos = s.find_first_of('A');
		string u = s.substr(0, pos + 1);
		s = s.substr(pos + 1);
		val += x24[u];
	}
	sum += val * code;
	code = 638;
	s = calc("^^AvA<^^Avvv>A");
	//code = 379;
	//s = calc("^A<<^^A>>AvvvA");
	val = 0;
	while (s.size() > 0) {
		size_t pos = s.find_first_of('A');
		string u = s.substr(0, pos + 1);
		s = s.substr(pos + 1);
		val += x24[u];
	}
	sum += val * code;

	cout << sum << endl;
}

