#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define pi (4.0*atan(1.0))
#define e 2.718281828

/*
 * 使用gcc编译提交，由于优化太严重，导致结果不对。
 * 使用g++成功。
 */

double strling(double n)
{
	return log2(2*pi*n)/2+n*log2(n/e);
}

int solve(int k)
{
	int case1, case2;
	int hi, lo, mid;

	lo = 1, hi = 1<<22;
	mid = (lo + hi)/2;

	while (lo <= hi) {
		case1 = k < strling(mid);
		case2 = k > strling(mid+1);

		if (case1)
			hi = mid;
		else if (case2)
			lo = mid + 1;
		else
			return mid;

		mid = (lo + hi)/2;
	}
	return lo;
}

int main()
{
	int year;
	int ans;

	while (scanf("%d", &year), year) {
		ans = solve(1<<(2+(year-1960)/10));
		printf("%d\n", ans);
	}
	return 0;
}

