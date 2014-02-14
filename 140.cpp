#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <string>
#include <cstring>

/*
 * 一直WA，后来重写一遍，发现原来输出时用的order数组...
 */

using namespace std;

bool G[26][26], vis[26];
int order[26], ans[26];
int n;
int _min;

bool dfs(int u, int& curval)
{
	vector<int> edge;

	vis[u] = true;
	for (int v = 0; v < 26; ++v)
		if (G[u][v]) {
			edge.push_back(v);
			int dis = abs(find(order, order + n, u) - find(order, order + n, v));
			curval = max(curval, dis);
		}
	if (curval >= _min)
		return false;
	for (int i = 0; i < edge.size(); ++i)
		if (!vis[edge[i]] && !dfs(edge[i], curval))
			return false;
	return true;
}

int main()
{
	string line;

	while (cin >> line, line != "#") {
		memset(G, 0, sizeof(G));
		memset(vis, 0, sizeof(vis));
		for (int i = 0, j = 0; i < line.length(); i = j + 1) {
			int p1 = line[i] - 'A';
			vis[p1] = true;
			i += 2;
			for (j = i; j < line.length() && line[j] != ';'; ++j) {
				G[p1][line[j] - 'A'] = G[line[j] - 'A'][p1] = true;
				vis[line[j] - 'A'] = true;
			}
		}
		n = accumulate(vis, vis + 26, 0);
		for (int i = 0, j = 0; i < 26; ++i)
			if (vis[i])
				order[j++] = i;

		_min = 0x7fff;
		do {
			memset(vis, 0, sizeof(vis));
			int curval = 0;
			if (dfs(order[0], curval) && curval < _min) {
				_min = curval;
				copy(order, order + n, ans);
			}
		} while (next_permutation(order, order + n));
		for (int i = 0; i < n; ++i)
			cout << char(ans[i] + 'A') << " ";
		cout << "-> " << _min << endl;
	}
	return 0;
}
