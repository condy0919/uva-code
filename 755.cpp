#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <cctype>

using namespace std;

char replacement[128];

void init_replacement()
{
	replacement['A'] = replacement['B'] = replacement['C'] = '2';
	replacement['D'] = replacement['E'] = replacement['F'] = '3';
	replacement['G'] = replacement['H'] = replacement['I'] = '4';
	replacement['J'] = replacement['K'] = replacement['L'] = '5';
	replacement['M'] = replacement['N'] = replacement['O'] = '6';
	replacement['P'] = replacement['R'] = replacement['S'] = '7';
	replacement['T'] = replacement['U'] = replacement['V'] = '8';
	replacement['W'] = replacement['X'] = replacement['Y'] = '9';
	replacement['0'] = '0';
	replacement['1'] = '1';
	replacement['2'] = '2';
	replacement['3'] = '3';
	replacement['4'] = '4';
	replacement['5'] = '5';
	replacement['6'] = '6';
	replacement['7'] = '7';
	replacement['8'] = '8';
	replacement['9'] = '9';
}

void replace_with_num(string& str)
{
	string::iterator iter;

	for (iter = str.begin(); iter != str.end(); ++iter) {
		if (isalnum(*iter)) {
			*iter = replacement[*iter];
		} else {
			str.erase(iter);
			--iter;
		}
	}
	str.insert(3, 1, '-');
}

int main()
{
	int total_test;
	int n;
	string str;
	map<string, int> tel;

	init_replacement();

	cin >> total_test;

	while (total_test-- > 0) {
		cin >> n;

		cin.ignore();
		while (n-- > 0) {
			cin >> str;

			replace_with_num(str);
			tel[str]++;
		}

		bool no_duplicate = true;
		for (map<string, int>::iterator it = tel.begin(); it != tel.end(); ++it)
			if (it->second > 1) {
				no_duplicate = false;
				cout << it->first << " " << it->second << endl;
			}
		if (no_duplicate)
			cout << "No duplicates." << endl;

		tel.clear();
		if (total_test != 0)
			cout << endl;
	}

	return 0;
}

