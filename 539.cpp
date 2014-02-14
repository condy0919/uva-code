#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int n, m;
bool G[25][25], vis[25][25];
int _max;

void dfs(int u, int len)
{
	bool flag = false;

	for (int v = 0; v < n; ++v)
		if (G[u][v] && !vis[u][v]) {
			flag = true;
			vis[u][v] = vis[v][u] = true;
			dfs(v, len + 1);
			vis[u][v] = vis[v][u] = false;
		}
	if (!flag)
		_max = max(_max, len);
}

int main()
{
	int x, y;

	while (cin >> n >> m, n || m) {
		memset(G, 0, sizeof(G));
		memset(vis, 0, sizeof(vis));
		_max = 0;
		for (int i = 0; i < m; ++i) {
			cin >> x >> y;
			G[x][y] = G[y][x] = true;
		}
		for (int i = 0; i < n; ++i)
			dfs(i, 0);
		cout << _max << endl;
	}
	return 0;
}
