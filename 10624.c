#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 这个暴力差点没有过。2.7s了.
 */

char a[30];
int n, m;

int divided(int i)
{
	if (i == 1)
		return 1;
	if (i == 2)
		return a[i - 1] % 2 == 0;
	if (i == 5)
		return a[i - 1] % 5 == 0;

	int sum = 0, j;

	for (j = 0; j < i; ++j)
		sum = (10 * sum + a[j]) % i;
	return sum == 0;
}

/*
 * [0, n-1), [n-1, m-1]
 */
int dfs(int cur)
{
	int i, start;
	if (cur == m)
		return 1;

	start = (cur == 0) ? 1 : 0;
	for (i = start; i <= 9; ++i) {
		a[cur] = i;
		/* cannot be divided */
		if (cur >= n - 1 && !divided(cur + 1))
			continue;
		if (dfs(cur + 1))
			return 1;
	}
	return 0;
}

int main()
{
	int t = 0, cases;
	scanf("%d", &cases);

	while (t < cases) {
		scanf("%d%d", &n, &m);
		int ans = dfs(0);
		printf("Case %d: ", ++t);
		if (!ans) {
			puts("-1");
		} else {
			int i;
			for (i = 0; i < m; ++i)
				printf("%c", a[i] + '0');
			puts("");
		}
	}
	
	return 0;
}
