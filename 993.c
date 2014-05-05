#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int charcmp(const void* a, const void* b)
{
	return *(char*)a - *(char*)b;
}

void solve(int N)
{
	int i, n = 0;
	char output[15] = {0};

	while (N > 1) {
		for (i = 9; i >= 2; --i)
			if (N % i == 0) {
				output[n++] = i + '0';
				N /= i;
				break;
			}
		if (i == 1) {
			puts("-1");
			return;
		}
	}
	qsort(output, n, sizeof(char), charcmp);
	puts(output);
}

int main()
{
	int T, N, ans;
	scanf("%d", &T);
	while (T-- > 0) {
		scanf("%d", &N);
		if (N == 1) {
			puts("1");
			continue;
		}
		solve(N);
	}
	return 0;
}
