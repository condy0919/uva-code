#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>
#include <cstdio>
#include <cstdlib>

/*
 * 一开始直接TLE了啊，DFS写错了啊。。。
 * 后来看了别人AC的代码之后，才发现我的思路和他们是一样的，果然我的代码写的少了。。。
 * 思路是一样的，就是写不对啊。。。
 */

using namespace std;

int N;
vector<int> G[101];
bool vis[101];
int en[101];
int add[101];

bool bfs(int u)
{
	queue<int> Q;
	bool visit[101] = {false};

	Q.push(u);
	visit[u] = true;
	int e;

	while (!Q.empty()) {
		e = Q.front(); Q.pop();
		for (int i = 0; i < G[e].size(); ++i)
			if (!visit[G[e][i]]) {
				if (G[e][i] == N)
					return true;
				visit[G[e][i]] = true;
				Q.push(G[e][i]);
			}
	}
	return false;
}

int dfs(int u, int energy)
{
	if (u == N)
		return true;

	for (int i = 0; i < G[u].size(); ++i) {
		if (!vis[G[u][i]]) {
			vis[G[u][i]] = true;
			en[G[u][i]] = energy + add[G[u][i]];
			if (en[G[u][i]] > 0 && dfs(G[u][i], energy + add[G[u][i]]))
				return true;
		} else if (energy + add[G[u][i]] > en[G[u][i]] && bfs(G[u][i]))
			return true;
	}
	return false;
}

int main()
{
	int i, j;
	int e, adj_num;
	int x;

	while (cin >> N, N != -1) {
		for (i = 1; i <= 100; ++i) {
			G[i].clear();
			en[i] = 0xffff;
		}
		memset(add, 0, sizeof(add));
		memset(vis, 0, sizeof(vis));
		for (i = 1; i <= N; ++i) {
			cin >> e >> adj_num;
			add[i] = e;
			for (j = 0; j < adj_num; ++j) {
				cin >> x;
				G[i].push_back(x);
			}
		}
		if (dfs(1, 100))
			puts("winnable");
		else
			puts("hopeless");
	}
	return 0;
}

