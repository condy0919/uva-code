#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gcd(int a, int b)
{
	int r;

	while (b != 0) {
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}

int main()
{
	int N;
	int i;
	long a, b;
	char s[31];

	scanf("%d", &N);
	for (i = 0; i < N; ++i) {
		scanf("%s", s);
		a = strtol(s, NULL, 2);
		scanf("%s", s);
		b = strtol(s, NULL, 2);

		printf("Pair #%d: ", i + 1);
		if (gcd(a, b) == 1)
			puts("Love is not all you need!");
		else
			puts("All you need is love!");
	}
	return 0;
}
