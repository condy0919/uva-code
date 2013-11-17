#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 原来是没有多重路的..
 */

int N, R;
int n;
int vis[201];
int G[201][201];
int deg[201];

int degree_error()
{
	int i;
	for (i = 0; i < N; ++i)
		if (deg[i] % 2)
			return 1;
	return 0;
}

void dfs(int v)
{
	int i;

	++n;
	vis[v] = 1;
	for (i = 0; i < N; ++i)
		if (G[v][i] && !vis[i])
			dfs(i);
}

int connect()
{
	n = 0;
	dfs(0);
	return n == N;
}

int main()
{
	int i;
	int x, y;

	while (scanf("%d%d", &N, &R) == 2) {
		memset(G, 0, sizeof(G));
		memset(vis, 0, sizeof(vis));
		memset(deg, 0, sizeof(deg));
		for (i = 0; i < R; ++i) {
			scanf("%d%d", &x, &y);
			G[x][y] = G[y][x] = 1;
			++deg[x];
			++deg[y];
		}

		if (degree_error() || !connect())
			printf("Not Possible\n");
		else
			printf("Possible\n");
	}
	return 0;
}

