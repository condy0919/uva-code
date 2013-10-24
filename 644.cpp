#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

vector<string> symbols;

bool cmp(const string& a, const string& b)
{
	return a.length() < b.length();
}

bool is_prefix(const string& a, const string& b)
{
	int i, j;

	for (i = j = 0; i < a.length(); ++i, ++j)
		if (a[i] != b[j])
			return false;
	return true;
}

bool process()
{
	int i, j;

	for (i = 0; i < symbols.size(); ++i)
		for (j = i + 1; j < symbols.size(); ++j)
			if (is_prefix(symbols[i], symbols[j]))
				return false;
	return true;
}

int main()
{
	string str;
	int round = 0;

	while (cin >> str) {
		if (str != "9")
			symbols.push_back(str);
		else {
			sort(symbols.begin(), symbols.end(), cmp);
			bool ans = process();

			cout << "Set " << ++round << " is ";
			if (!ans)
				cout << "not ";
			cout << "immediately decodable\n";

			symbols.clear();
		}
	}
	return 0;
}
