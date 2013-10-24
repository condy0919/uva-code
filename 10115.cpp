#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

vector<string> find_string, replace_string;

int main()
{
	int rules;
	string ori;

	while (cin >> rules, rules > 0) {
		cin.ignore();

		find_string.resize(rules);
		replace_string.resize(rules);

		for (int i = 0; i < rules; ++i) {
			getline(cin, find_string[i]);
			getline(cin, replace_string[i]);
		}

		getline(cin, ori);

		int k = 0;
		string::size_type pos;
		while (k < rules) {
			while ((pos = ori.find(find_string[k])) != string::npos)
				ori.replace(pos, find_string[k].length(), replace_string[k]);
			++k;
		}
		cout << ori << endl;
	}
	return 0;
}

