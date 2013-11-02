#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int n_[13];

long long int fact(int n)
{
	static long long int F[13] = {1, 1, 2};

	if (F[n])
		return F[n];
	return F[n] = (long long int)(n)*fact(n-1);
}

long long int c(int n, int m)
{
	if (n <= 0)
		return 1;
	if (m == 1)
		return n;
	return fact(n)/(fact(m)*fact(n-m));
}

long long int calc(int n, int k)
{
	long long int ret = 1;
	int i;
	int t = n;

	for (i = 0; i < k; ++i) {
		if (n_[i] == 0)
			continue;
		ret *= c(t, n_[i]);
		t -= n_[i];
	}
	return ret;
}

int main()
{
	int k, n;
	int i;

	while (scanf("%d%d", &n, &k) == 2) {
		for (i = 0; i < k; ++i)
			scanf("%d", &n_[i]);
		printf("%d\n", calc(n, k));
	}
	return 0;
}

