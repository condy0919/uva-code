#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int N;
int a[50];

int gcd(int a, int b)
{
	int r;
	while (b) {
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}

int main()
{
	int i, j;
	int total, pairs;

	while (scanf("%d", &N), N) {
		for (i = 0; i < N; ++i)
			scanf("%d", &a[i]);
		pairs = 0;
		total = (N - 1) * N / 2;

		for (i = 0; i < N; ++i)
			for (j = i + 1; j < N; ++j)
				if (gcd(a[i], a[j]) == 1)
					++pairs;
		if (pairs == 0)
			puts("No estimate for this data set.");
		else
			printf("%lf\n", sqrt(6.0 * total / pairs));
	}
	return 0;
}
