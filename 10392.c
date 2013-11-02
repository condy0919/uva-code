#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define PRIME 0
#define NOT_PRIME 1

char is_prime[1000000+1];
int prime_list[80000];
int prime_list_size;

void init_prime_list()
{
	int i, j, k;
	int n = 0, m;
	int t;

	for (i = 4; i < 1000000+1; i += 2)
		is_prime[i] = NOT_PRIME;
	for (i = 6; i < 1000000+1; i += 3)
		is_prime[i] = NOT_PRIME;

	for (i = 1; n < 1000000+1; ++i) {
		m = 6 * i;
		for (j = 0; j < 2; ++j) {
			n = m - 1 + 2 * j;
			if (n < 1000000+1 && is_prime[n] == PRIME)
				for (k = 2 * n; k < 1000000+1; k += n)
					is_prime[k] = NOT_PRIME;
		}
	}
	for (prime_list_size = 0, i = 2; i < 1000000+1; ++i)
		if (is_prime[i] == PRIME)
			prime_list[prime_list_size++] = i;
}

int main()
{
	long long int n;
	int i;
	int flag;

	init_prime_list();
	while (scanf("%ld", &n), n != -1) {
		/* factor n */
		flag = 0;
		if (n < 1000000 && is_prime[n] == PRIME) {
			printf("    %d\n", n);
			continue;
		}
		for (i = 0; i < prime_list_size && n > 1; ++i)
			while (n % prime_list[i] == 0) {
				printf("    %d\n", prime_list[i]);
				n /= prime_list[i];
				flag = 1;
			}
		if (!flag)
			printf("    %ld\n", n);
		else if (n != 1)
			printf("    %ld\n", n);
		putchar('\n');
	}

	return 0;
}

