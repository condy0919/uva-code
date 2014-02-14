#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
#include <cstring>

/*
 * 原来只要子串中有目标串也可以啊。。。这个不知道。
 */

using namespace std;

#define HASHSIZE (1 << 16)

string a, b, w, z;
int hashtable[HASHSIZE];

int hash(const string& s)
{
	int ret = 0;
	for (int i = 0; i < s.length(); ++i)
		ret = 2 * ret + (s[i] - 'a' + 1);
	return ret;
}

bool bfs()
{
	queue<string> Q;
	int z_hashval = hash(z);

	memset(hashtable, 0, sizeof(hashtable));
	for (int i = 0; i < w.length(); ++i) {
		int l = min(w.length() - i, z.length());
		string s = w.substr(i, l);
		int hashval = hash(s);

		if (!hashtable[hashval]) {
			hashtable[hashval] = true;
			Q.push(s);
		}
	}

	while (!Q.empty()) {
		if (hashtable[z_hashval])
			return true;
		string t = Q.front(); Q.pop();
		string e = "";

		for (int i = 0; i < t.length(); ++i)
			e += (t[i] == 'a' ? a : b);

		for (int i = 0; i < e.length(); ++i) {
			int l = min(e.length(), z.length());
			string s = e.substr(i, l);
			int hashval = hash(s);

			if (!hashtable[hashval]) {
				hashtable[hashval] = true;
				Q.push(s);
			}
		}
	}
	return false;
}

int main()
{
	while (cin >> a >> b >> w >> z) {
		if (z[0] == '\0')
			cout << "NO\n";
		else
			cout << (bfs() ? "YES\n" : "NO\n");
	}
	return 0;
}
