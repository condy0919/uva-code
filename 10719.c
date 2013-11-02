#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 10000

int p[N], q[N];
int asp;

int main()
{
	int k, ch;
	int i, j;

	while (scanf("%d", &k) == 1) {
		getchar();
		asp = 0;
		do {
			scanf("%d", &p[asp]);
			++asp;
			ch = getchar();
		} while (ch != '\n');

		for (i = 0; i < asp - 1; ++i) {
			q[i] = p[i];
			p[i + 1] += k * p[i];
		}
		q[i] = p[i];
		printf("q(x):");
		for (j = 0; j < i; ++j)
			printf(" %d", q[j]);
		printf("\nr = %d\n\n", q[j]);
	}
	return 0;
}
