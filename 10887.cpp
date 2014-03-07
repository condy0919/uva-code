#include <iostream>
#include <algorithm>
#include <string>
#include <set>

/*
 * 竟然有空串，题目不是说由a-z组成的吗？
 */

using namespace std;

int calc(set<string>& a, set<string>& b)
{
	typedef set<string>::iterator iter_t;
	set<string> concatention;
	for (iter_t i = a.begin(); i != a.end(); ++i)
		for (iter_t j = b.begin(); j != b.end(); ++j) {
			string s = *i + *j;
			concatention.insert(s);
		}
	return concatention.size();
}

int main()
{
	int T;
	int as, bs;

	cin >> T;
	for (int cases = 0; cases < T; ++cases) {
		cout << "Case " << cases + 1 << ": ";
		cin >> as >> bs;
		cin.ignore();
		set<string> a, b;
		string s;
		for (int i = 0; i < as; ++i) {
			getline(cin, s);
			a.insert(s);
		}
		for (int i = 0; i < bs; ++i) {
			getline(cin, s);
			b.insert(s);
		}
		cout << calc(a, b) << endl;
	}
	return 0;
}
