#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
 * 数据范围看错了，原来是2^32-1.
 * 还有一个理解错误的地方是：去一次，来一次分别算了。
 * 小错误犯的比较多.
 */

int check(unsigned int n)
{
	unsigned int s = sqrt(n);

	if (s * s == n)
		return 1;
	return 0;
}

int main()
{
	unsigned int n;
	
	while (scanf("%u", &n), n) {
		if (check(n))
			puts("yes");
		else
			puts("no");
	}
	return 0;
}

