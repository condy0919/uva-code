#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define dif(A, B, n) (fabs(log(B)/log(A)-log(n)/log(n+1)))

/*
 * 一开始没有考虑到 log(A)/log(n+1) 的精度损失。
 * gcc优化又过头了。改用g++就行了。
 */

int main()
{
	int A, B;
	int k, n;
	int temp;
	double ans1, ans2;

	while (scanf("%d%d", &A, &B), A || B) {
		if (A < B) {
			temp = A;
			A = B;
			B = temp;
		}

		for (n = 1; dif(A, B, n) > 1e-10; ++n)
			;
		k = round(log(A)/log(n+1));

		if (n == 1)
			ans1 = k;
		else
			ans1 = round((pow(n, k) - 1)/(n - 1));
		ans2 = -1*pow(n, k+1) + pow(1+n, k+1);
		printf("%d %d\n", (int)ans1, (int)ans2);
	}
	return 0;
}

