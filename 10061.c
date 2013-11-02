#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define pi (4*atan(1.0))
#define e 2.718281828
#define log_(base, x) (log(x)/log(base))
#define IS_PRIME 0
#define NOT_PRIME 1

/*
 * 使用strling公式。
 * 注意小数据时的特殊情况，因为strling只是公式，有误差。
 * 但log后误差随着n的增大而减小，但n较小时仍有偏差。
 */

int prime_list[150];
int primes_size;
char is_prime[800];

void init_prime_list()
{
	int i, j, k;
	int n, m = 0;

	for (i = 4; i < 800; i += 2)
		is_prime[i] = NOT_PRIME;
	for (i = 6; i < 800; i += 3)
		is_prime[i] = NOT_PRIME;

	is_prime[1] = is_prime[4] = NOT_PRIME;
	for (i = 1; m < 800; ++i) {
		m = 6 * i;
		for (j = 0; j < 2; ++j) {
			n = m - 1 + 2 * j;
			if (n < 800 && is_prime[n] == IS_PRIME)
				for (k = 2 * n; k < 800; k += n)
					is_prime[k] = NOT_PRIME;
		}
	}
	for (i = 2; i < 800; ++i)
		if (is_prime[i] == IS_PRIME)
			prime_list[primes_size++] = i;
}

int solve(int base, int n)
{
	int old = base;
	int i, j;
	int power[800] = {0};
	char visit[800] = {0};
	int min = 0x7fffffff;
	int t;

	for (i = 0; old > 1; ++i) {
		while (old > 0 && old % prime_list[i] == 0) {
			old /= prime_list[i];
			++power[prime_list[i]];
		}
	}

	for (i = 2; i < 800; ++i) {
		if (power[i] == 0)
			continue;
		/* i is one of the factors */
		for (t = 0, j = 1; n / (int)pow(i, j) > 0; ++j)
			t += n/(int)pow(i, j);
		if (min > t/power[i])
			min = t/power[i];
		power[i] = 0;/* in case of n! < base case */
	}

	for (i = 0, t = 0; i < 800; ++i)
		if (power[i] != 0) {
			t = 1;
			break;
		}
	return t ? 0 : min;
}

int main()
{
	int n, base;
	int digits, zeros;
	int fac;
	int i;
	int old;

	init_prime_list();
	while (scanf("%d%d", &n, &base) == 2) {
		if (n <= 12) {
			digits = zeros = 0;
			for (fac = 1, i = 2; i <= n; ++i)
				fac *= i;
			for (old = fac; old > 0; old /= base)
				++digits;
			for (old = fac; old > 0 && old % base == 0; ++zeros)
				old /= base;
		} else {
			digits = ceil((log_(base,2*pi)+log_(base,n))/2.0+n*log_(base,n/e));
			zeros = solve(base, n);
		}
		printf("%d %d\n", zeros, digits);
	}
	return 0;
}

