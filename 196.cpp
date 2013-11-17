#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cctype>

/*
 * recursive descent..
 */

using namespace std;

#define FORMULA false
#define VALUE true

struct xy_t {
	int x, y;

	xy_t(int _x, int _y):x(_x), y(_y) {}
};

struct elem_t {
	bool type;

	string formula;
	int val;
};

vector< vector<elem_t> > vec;


xy_t translate(string& str)
{
	int r = 0, c = 0;
	string::iterator i;

	for (i = str.begin(); isupper(*i); ++i)
		c = 26 * c + (*i - 'A' + 1);
	for (; i != str.end(); ++i)
		r = 10 * r + (*i - '0');
	return xy_t(r - 1, c - 1);
}

int calc(string&);
int _calc(string);

int _calc(string str)
{
	xy_t xy = translate(str);
	int x = xy.x, y = xy.y;

	if  (vec[x][y].type == VALUE)
		return vec[x][y].val;
	vec[x][y].val = calc(vec[x][y].formula);
	vec[x][y].type = VALUE;
	return vec[x][y].val;
}

int calc(string& str)
{
	string::size_type pos;
	int ret = 0;

	do {
		pos = str.find('+');
		ret += _calc(str.substr(0, pos));
		if (pos != string::npos)
			str = str.substr(pos + 1);
	} while (pos != string::npos);
	return ret;
}



int main()
{
	int row, col;
	int T;

	cin >> T;
	while (T-- > 0) {
		cin >> col >> row;
		vec.clear();
		vec.resize(row);
		for (int i = 0; i < row; ++i)
			vec[i].resize(col);

		string s;
		for (int i = 0; i < row; ++i)
			for (int j = 0; j < col; ++j) {
				cin >> s;
				if (s[0] == '=') {
					vec[i][j].type = FORMULA;
					vec[i][j].formula = s.substr(1);
				} else {
					vec[i][j].type = VALUE;
					vec[i][j].val = atoi(s.c_str());
				}
			}
		for (int i = 0; i < row; ++i)
			for (int j = 0; j < col; ++j)
				if (vec[i][j].type == FORMULA) {
					vec[i][j].val = calc(vec[i][j].formula);
					vec[i][j].type = VALUE;
				}
		for (int i = 0; i < row; ++i) {
			cout << vec[i][0].val;
			for (int j = 1; j < col; ++j)
				cout << " " << vec[i][j].val;
			cout << endl;
		}
	}
	return 0;
}
