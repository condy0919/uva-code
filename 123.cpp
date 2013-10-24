#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>


using namespace std;

struct elem_t {
	string ori;
	string keyword;
};

char Tolower(char ch)
{
	return tolower(ch);
}

char Toupper(char ch)
{
	return toupper(ch);
}

bool cmp(const elem_t& a, const elem_t& b)
{
	return a.keyword < b.keyword;
}

int first_char(const string& str, int ed)
{
	int i;
	for (i = ed; i < str.length() && !isalpha(str[i]); ++i)
		;
	return i;
}

int last_char(const string& str, int st)
{
	int i;
	for (i = st; i < str.length() && isalpha(str[i]); ++i)
		;
	return i;
}

int main()
{
	string str;
	vector<string> ignore_words;
	vector<elem_t> vec;

	while (cin >> str, str != "::")
		ignore_words.push_back(str);
	// recv ignore words done

	cin.ignore();
	while (getline(cin, str)) {
		if (str.length() == 0)
			continue;
		transform(str.begin(), str.end(), str.begin(), Tolower);

		int st, ed = 0;
		while (ed != str.length()) {
			st = first_char(str, ed);
			ed = last_char(str, st);

			if (st == str.length())
				break;

			string s(str.begin() + st, str.begin() + ed);

			vector<string>::iterator ret = find(ignore_words.begin(), ignore_words.end(), s);

			if (ret == ignore_words.end()) {// not ignore words
				transform(str.begin() + st, str.begin() + ed, str.begin() + st, Toupper);
				elem_t e = { str, s };
				vec.push_back(e);
				transform(str.begin() + st, str.begin() + ed, str.begin() + st, Tolower);
			}
		}
	}
	//sort(vec.begin(), vec.end(), cmp);
	stable_sort(vec.begin(), vec.end(), cmp);
	for (int i = 0; i < vec.size(); ++i)
		cout << vec[i].ori << endl;

	return 0;
}
