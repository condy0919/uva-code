#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <cctype>
#include <cstdio>

using namespace std;

struct elem_t {
	char ch;
	int rows, cols;

	elem_t(char _ch = 0, int _r = 0, int _c = 0):ch(_ch), rows(_r), cols(_c) {}
};

elem_t pool[26];
int pos[26];
int n;

void init_pos()
{
	for (int i = 0; i < n; ++i)
		pos[pool[i].ch - 'A'] = i;
}

int solve(const vector<elem_t>& vec)
{
	stack<elem_t> S;
	int i, ret = 0;

	for (i = 0; i < vec.size(); ++i) {
		if (vec[i].ch == '(' || vec[i].ch == 0) {
			S.push(vec[i]);
		} else if (vec[i].ch == ')') {
			elem_t e1, e2;

			if (S.empty())
				continue;
			e2 = S.top();
			S.pop();
			if (S.top().ch == '(') {
				S.pop();
				S.push(e2);
				continue;
			}
			e1 = S.top();
			S.pop();
			if (e1.cols != e2.rows)
				return -1;
			S.pop();// pop the `('
			ret += e1.rows * e1.cols * e2.cols;
			S.push(elem_t(0, e1.rows, e2.cols));
		}
	}
	return ret;
}

void convert(const string& str, vector<elem_t>& vec)
{
	for (int i = 0; i < str.length(); ++i) {
		if (str[i] == '(' || str[i] == ')') {
			vec.push_back(elem_t(str[i]));
		} else {
			int p = pos[str[i] - 'A'];
			vec.push_back(elem_t(0, pool[p].rows, pool[p].cols));
		}
	}
}

int main()
{
	vector<elem_t> vec;
	string str;
	int ch;

	cin >> n;
	cin.ignore();
	for (int i = 0; i < n; ++i) {
		cin >> pool[i].ch >> pool[i].rows >> pool[i].cols;
		cin.ignore();
	}
	init_pos();
	while (cin >> str) {
		vec.clear();
		convert(str, vec);
		int ans = solve(vec);
		if (ans == -1)
			cout << "error" << endl;
		else
			cout << ans << endl;
	}

	return 0;
}
