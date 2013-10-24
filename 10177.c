#include <stdio.h>
#include <math.h>
#include <stdint.h>

int main()
{
	int64_t n;
	int64_t s2, r2, s3, r3, s4, r4;
	int64_t t;

	while (scanf("%ld", &n) == 1) {
		t = n*(n+1)/2;

		s2 = t * (2*n+1)/3;
		r2 = t*t - s2;

		s3 = t*t;
		r3 = t*t*t - s3;

		s4 = t * (1+2*n)*(3*n*n+3*n-1)/15;
		r4 = t*t*t*t - s4;

		printf("%ld %ld %ld %ld %ld %ld\n", s2, r2, s3, r3, s4, r4);
	}
	return 0;
}

