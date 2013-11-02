#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int z, i, m, l;

char visit[10000];
int order[10000];

int calc()
{
	int t = 0;
	memset(visit, 0, sizeof(visit));

	do {
		visit[l] = 1;
		order[l] = t;
		l = (z * l + i) % m;
		++t;
	} while (!visit[l]);
	return t - order[l];
}

int main()
{
	int round = 1;
	int ans;

	while (scanf("%d%d%d%d", &z, &i, &m, &l),z||i||m||l) {
		ans = calc();
		printf("Case %d: %d\n", round++, ans);
	}
	return 0;
}

