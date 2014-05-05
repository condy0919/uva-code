#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

bool check(string& s, vector<string>& sv, int len)
{
	bool vis[300] = {false};
	int cnt = 0;

	for (int i = 0; i < sv.size() / 2; ++i) {
		if (vis[i])
			continue;

		for (int j = sv.size() - 1; j > i; --j) {
			if (vis[j])
				continue;
			if (sv[i].length() + sv[j].length() != len)
				continue;
			if (s == sv[i] + sv[j] || s == sv[j] + sv[i]) {
				vis[i] = vis[j] = true;
				++cnt;
				break;
			}
		}
	}
	return cnt == sv.size() / 2;
}

int main()
{
	int T, len;
	string out, s;

	cin >> T;
	cin.ignore();
	getline(cin, s);
	while (T-- > 0) {
		vector<string> sv;
		while (getline(cin, s) && !s.empty())
			sv.push_back(s);
		sort(sv.begin(), sv.end(), [](const string& a, const string& b) { return a.length() < b.length(); });

		len = sv.front().length() + sv.back().length();
		for (int i = 0; i < sv.size() && sv[i].length() == sv.front().length(); ++i)
			for (int j = sv.size() - 1; j > i && sv[j].length() == sv.back().length(); --j) {
				out = sv[i] + sv[j];
				if (check(out, sv, len))
					goto result;

				out = sv[j] + sv[i];
				if (check(out, sv, len))
					goto result;
			}
result:
		cout << out << endl;
		if (T)
			cout << endl;
	}
	return 0;
}
