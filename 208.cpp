#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdio>

/*
 * 初看觉得很简单，深搜+回溯就可以解决了。但结果总是那么的。。。
 * 后来觉得可能是采用了邻接矩阵的方式，改为邻接表还是TLE。。。
 * 看来不prune是过不了了。。。于是preprocess，采用floyd-warshell来
 * 判断当前dfs的点是否可达。。。
 */

using namespace std;

#define N 22

bool G[N][N], T[N][N], vis[N];
int dest;
int cnt;

void dfs(int u, vector<int>& path)
{
	vis[u] = true;
	path.push_back(u);

	if (u == dest) {
		++cnt;
		cout << path[0];
		for (int i = 1; i < path.size(); ++i)
			cout << " " << path[i];
		cout << endl;
		return;
	}
	for (int v = 0; v < N; ++v)
		if (G[u][v] && T[v][dest] && !vis[v]) {
			dfs(v, path);
			vis[v] = false;
			path.pop_back();
		}
}

int main()
{
	int round = 0;
	int x, y;
	vector<int> path;

	while (cin >> dest) {
		memset(G, 0, sizeof(G));
		memset(vis, 0, sizeof(vis));
		cnt = 0;
		path.clear();
		while (cin >> x >> y, x || y)
			G[x][y] = G[y][x] = true;

		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				T[i][j] = G[i][j];
		for (int k = 1; k < N; ++k)
			for (int i = 1; i < N; ++i)
				for (int j = 1; j < N; ++j)
					T[i][j] |= T[i][k] & T[k][j];
		printf("CASE %d:\n", ++round);
		dfs(1, path);
		printf("There are %d routes from the firestation to streetcorner %d.\n", cnt, dest);
	}
    return 0;
}
