#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <limits>

/*
 * 这道题啊，匹配描述的不清楚啊。
 * http://hi.baidu.com/zyz913614263/item/7bd90a4474cd82f7bcf45166
 */

using namespace std;

struct filename_t {
	string base, ext;

	filename_t() {}
	filename_t(const string& s) {
		if (s.find_first_of('.') == string::npos) {
			base = s;
			ext = "";
		} else {
			int pos = s.find_first_of('.');
			base = s.substr(0, pos);
			ext = s.substr(pos + 1);
		}
	}
};

string solve(const vector<filename_t>& deleted)
{
	const int inf = numeric_limits<int>::max();
	int len;
	string ret;

	// for base name of a filename
	len = inf;
	for (int i = 0; i < deleted.size(); ++i)
		if (len > deleted[i].base.length())
			len = deleted[i].base.length();
	for (int i = 0; i < len; ++i) {
		bool flag = false;
		for (int j = 1; j < deleted.size(); ++j)
			if (deleted[0].base[i] != deleted[j].base[i]) {
				flag = true;
				break;
			}
		ret += (flag ? '?' : deleted[0].base[i]);
	}
	for (int i = 0; i < deleted.size(); ++i)
		if (len != deleted[i].base.length()) {
			ret += '*';
			break;
		}

	ret += '.';

	// for extension
	len = inf;
	for (int i = 0; i < deleted.size(); ++i)
		if (len > deleted[i].ext.length())
			len = deleted[i].ext.length();
	for (int i = 0; i < len; ++i) {
		bool flag = false;
		for (int j = 1; j < deleted.size(); ++j)
			if (deleted[0].ext[i] != deleted[j].ext[i]) {
				flag = true;
				break;
			}
		ret += (flag ? '?' : deleted[0].ext[i]);
	}
	for (int i = 0; i < deleted.size(); ++i)
		if (len != deleted[i].ext.length()) {
			ret += '*';
			break;
		}
	return ret;
}

bool check(const string& ans, string& kept)
{
	size_t dot1, dot2 = string::npos;

	for (int i = 0; i < ans.length(); ++i)
		if (ans[i] == '.') {
			dot1 = i;
			break;
		}

	for (int i = 0; i < kept.length(); ++i)
		if (kept[i] == '.') {
			dot2 = i;
			break;
		}

	if (dot2 == string::npos)
		dot2 = kept.length();

	for (int i = 0, k = 0; i < dot1; ++i, ++k)
		if (ans[i]!='?' && ans[i]!='*' && ans[i] != kept[k])
			return false;
		else if (ans[i] != '*' && k >= dot2)
			return false;
	if (dot1 < dot2 && ans[dot1 - 1] != '*')
		return false;

	for (int i = dot1 + 1, k = dot2 + 1; i < ans.length(); ++i, ++k)
		if (ans[i]!='?' && ans[i]!='*' && ans[i]!=kept[k])
			return false;
		else if (ans[i]!='*' && k >= kept.length())
			return false;
	if (ans.length() - dot1 < kept.length() - dot2 &&
			ans[ans.length() - 1]!='*')
		return false;
	return true;
}

int main()
{
	int T;
	string s;

	cin >> T;
	cin.ignore();
	getline(cin, s);
	while (T-- > 0) {
		vector<filename_t> deleted;
		vector<string> kept;

		while (getline(cin, s) && s != "") {
			if (s[0] == '-')
				deleted.push_back(filename_t(s.substr(1)));
			else
				kept.push_back(s.substr(1));
		}

		string ans = solve(deleted);
		bool flag = false;
		for (int i = 0; i < kept.size(); ++i)
			if (check(ans, kept[i])) {
				flag = true;
				break;
			}
		if (!flag)
			cout << "DEL " << ans << endl;
		else
			cout << "IMPOSSIBLE" << endl;

		if (T)
			cout << endl;
	}
	return 0;
}
