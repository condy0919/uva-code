#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define dif(A, B, n) (fabs(log(B)/log(A)-log(n)/log(n+1)))

int main()
{
	int A, B;
	int k, n;
	int i;
	int temp;
	double ans1, ans2;

	while (scanf("%d%d", &A, &B), A || B) {
		if (A < B) {
			temp = A;
			A = B;
			B = temp;
		}
		for (n = 1; dif(A, B, n) > 1e-6; ++n)
			;
		k = log(A)/log(n+1);

		if (n == 1)
			ans1 = k;
		else
			ans1 = (pow(n, k) - 1)/(n - 1);
		ans2 = 0.0;
		for (i = 1; i <= k + 1; ++i)
			ans2 += pow(n+1, k+1-i)*pow(n, i-1);
		printf("%d %d\n", (int)ans1, (int)ans2);
	}
	return 0;
}

