#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

/*
 * 自从有了中文翻译之后，题目都看不懂了。。果然自己还是要看英文的。。。
 * 自己想的算法总是错。。。
 */

struct elem_t {
	char face, suit;

	elem_t(char _f = 0, char _s = 0):face(_f), suit(_s) {}
};

bool cmp(const elem_t& a, const elem_t& b)
{
	return a.face == b.face || a.suit == b.suit;
}

vector< vector<elem_t> > L;

void solve()
{
	int i;
	int pos, dis;

	while (true) {
		bool flag = false;
		for (i = L.size() - 1; i >= 0; --i) {
			if (i - 3 >= 0 && cmp(L[i].back(), L[i-3].back())) {
				pos = i;
				dis = 3;
				flag = true;
			} else if (i - 1 >= 0 && cmp(L[i].back(), L[i-1].back())) {
				pos = i;
				dis = 1;
				flag = true;
			}
		}
		if (flag) {
			L[pos - dis].push_back(L[pos].back());
			L[pos].pop_back();
			if (L[pos].empty())
				L.erase(L.begin() + pos);
		} else
			break;
	}
}

int main()
{
	string line;
	vector<elem_t> x;
	elem_t e;

	while (getline(cin, line), line != "#") {
		L.clear();
		istringstream iss1(line);
		getline(cin, line);
		istringstream iss2(line);
		while (iss1 >> e.face >> e.suit) {
			x.clear();
			x.push_back(e);
			L.push_back(x);
		}
		while (iss2 >> e.face >> e.suit) {
			x.clear();
			x.push_back(e);
			L.push_back(x);
		}
		solve();
		string postfix = L.size() > 1 ? "s" : "";
		cout << L.size() << " pile" << postfix << " remaining:";
		for (int i = 0; i < L.size(); ++i)
			cout << " " << L[i].size();
		cout << endl;
	}
	return 0;
}
