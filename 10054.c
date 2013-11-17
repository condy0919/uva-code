#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 不知道怎么回事，以前写总是不对，今天一A了。
 */

int G[52][52];

int connect()
{
	int out[52] = {0};
	int i, j, so;

	for (i = 1; i <= 50; ++i) {
		so = 0;
		for (j = 1; j <= 50; ++j)
			so += G[i][j];
		out[i] = so;
	}
	for (i = 1; i <= 50; ++i)
		if (out[i] % 2)
			return 0;
	return 1;
}

void euler_path(int u)
{
	int v;

	for (v = 1; v <= 50; ++v)
		if (G[u][v] > 0) {
			--G[u][v];
			--G[v][u];
			euler_path(v);
			printf("%d %d\n", v, u);
		}
}

int main()
{
	int T, N;
	int i;
	int x, y;
	int round = 0;

	scanf("%d", &T);
	while (T-- > 0) {
		scanf("%d", &N);
		memset(G, 0, sizeof(G));
		
		for (i = 0; i < N; ++i) {
			scanf("%d%d", &x, &y);
			G[x][y]++;
			G[y][x]++;
		}
		printf("Case #%d\n", ++round);
		if (!connect()) {
			printf("some beads may be lost\n");
		} else {
			euler_path(x);
		}
		if (T)
			putchar('\n');
	}
	return 0;
}

