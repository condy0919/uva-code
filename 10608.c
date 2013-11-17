#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int p[30001];
int sum[30001];

int find(int x)
{
	if (x == p[x])
		return x;
	return p[x] = find(p[x]);
}

int main()
{
	int T;
	int M, N;
	int i, j;
	int A, B;
	int root;

	scanf("%d", &T);
	while (T-- > 0) {
		memset(sum, 0, sizeof(sum));
		scanf("%d%d", &N, &M);
		for (i = 1; i <= N; ++i)
			p[i] = i;
		for (i = 0; i < M; ++i) {
			scanf("%d%d", &A, &B);
			p[find(A)] = find(B);
		}
		for (i = 1; i <= N; ++i) {
			root = find(i);
			++sum[root];
		}
		j = 1;
		for (i = 1; i <= N; ++i)
			if (sum[i] > sum[j])
				j = i;
		printf("%d\n", sum[j]);
	}
	return 0;
}
