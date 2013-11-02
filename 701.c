#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * 再一次地被gcc的优化坑了一把。
 * 从而得到了结论：一般不可能超时的算法出现TLE很有可能就是优化的问题。
 * 换个编译器可能会得到解决。
 */

long long calc(long long x)
{
	int i;
	int len_x = (int)log10(x)+1;
	long long low, high;

	for (i = len_x + 1; 1; ++i) {
		low = ceil(log2(x) + i * log2(10.0));
		/*low = floor(log2(x) + i * log2(10.0));*/
		high = floor(log2(x+1) + i * log2(10.0));

		if (high == low)
			return high;
	}
	return high;
}


int main()
{
	unsigned int x;

	while (scanf("%u", &x) == 1)
		printf("%lld\n", calc(x));
	return 0;
}

