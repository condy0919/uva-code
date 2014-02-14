#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*
 * 照着http://www.cnblogs.com/ziyi--caolu/p/3330662.html来了一遍，
 * 原来bit这么有效率啊。这里关键的剪枝是cover数组，它里面保存的是
 * 从i-N点及其它们的邻接点所形成的覆盖区域，若当前的覆盖状态再加上
 * cover[]的覆盖仍不能达到最终的状态，则give up.
 */

#define set(v, n) \
	do {\
		(v) |= (1UL << (n));\
	} while (0)
#define allbit(n) ((1UL << (n)) - 1)

int N, M;
uint64_t adj[36], cover[36];

int dfs(int s, int cur_serv, uint64_t cover_state, int serv_limit)
{
	int i;

	if (cover_state == allbit(N))
		return 1;
	if (cur_serv >= serv_limit)
		return 0;

	for (i = s; i <= N; ++i) {
		if ((cover[i] | cover_state) != allbit(N))
			break;
		if ((cover_state | adj[i]) == cover_state)
			continue;

		if (dfs(i + 1, cur_serv + 1, cover_state | adj[i], serv_limit))
			return 1;
	}
	return 0;
}

int main()
{
	int i;
	int x, y;

	while (scanf("%d%d", &N, &M), N || M) {
		memset(adj, 0, sizeof(adj));
		for (i = 0; i < M; ++i) {
			scanf("%d%d", &x, &y);
			set(adj[x], y - 1);
			set(adj[y], x - 1);
		}
		for (i = 1; i <= N; ++i)
			set(adj[i], i - 1);
		cover[N] = adj[N];
		for (i = N - 1; i > 0; --i)
			cover[i] = (cover[i + 1] | adj[i]);
		for (i = 1; i <= N; ++i)
			if (dfs(1, 0, 0UL, i)) {
				printf("%d\n", i);
				break;
			}
	}
	return 0;
}
