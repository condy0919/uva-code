#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

void clear_noalpha(string& s)
{
	int i;
	
	for (i = 0; i < s.length(); ++i)
		if (!isalpha(s[i]))
			s[i] = ' ';
}


int main()
{
	string str;
	vector<string> vec;

	while (cin >> str) {
		clear_noalpha(str);
		for (int i = 0; i < str.length(); ++i)
			str[i] = tolower(str[i]);

		istringstream iss(str);
		string s;
		while (iss >> s)
			vec.push_back(s);
	}
	sort(vec.begin(), vec.end());

	int i, j;
	cout << vec[0] << endl;
	for (i = 0, j = 1; j < vec.size(); ++i, ++j)
		if (vec[i] != vec[j])
			cout << vec[j] << endl;
	return 0;
}

