#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * 我圧根就没有想到要用迭代加深搜索啊。。
 * 有时候还是要演算一下的啊。。。哪怕思路很清楚。
 */

int n;
int ans[1000];

int dfs(int cur, int limit)
{
	int i, j, k;
	int s;

	if (cur == limit)
		return ans[cur - 1] == n;

	for (i = 0; i < cur; ++i)
		for (j = i; j < cur; ++j)
			if (ans[i] + ans[j] > ans[cur - 1] && ans[i] + ans[j] <= n) {
			s = ans[i] + ans[j];
			for (k = cur; k < limit - 1; ++k)/* 一开始这里多算了一步，可就是这一步，TLE多次。只差了1啊。。。 */
				s *= 2;
			if (s < n)
				continue;

			ans[cur] = ans[i] + ans[j];
			if (dfs(cur + 1, limit))
				return 1;
		}
	return 0;
}

int main()
{
	int m, depth;
	int i;
	while (scanf("%d", &n), n) {
		memset(ans, 0, sizeof(ans));
		ans[0] = 1;

		m = 1, depth = 0;
		while (m < n) {
			m <<= 1;
			++depth;
		}
		while (!dfs(1, depth + 1))
			++depth;
		printf("%d", ans[0]);
		for (i = 1; i <= depth; ++i)
			printf(" %d", ans[i]);
		puts("");
	}
	return 0;
}
