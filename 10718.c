#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
 * 感谢Staginner的分析.
 */

unsigned int N, L, U;
int64_t M, t1, t2;

int main()
{
	int i;
	while (scanf("%u%u%u", &N, &L, &U) == 3) {
		M = 0;
		for (i = 31; i >= 0; --i) {
			if ((N >> i) & 1) {
				t2 = M | ((1UL << i) - 1);
				if (t2 < L)
					M |= (1UL << i);
			} else {
				t1 = M | (1UL << i);
				t2 = M | ((1UL << (i + 1)) - 1);
				if (t1 <= U && t2 >= L)
					M |= (1UL << i);
			}
		}
		printf("%lld\n", M);
	}
	return 0;
}
