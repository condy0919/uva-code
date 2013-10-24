#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define f(x) (x*(x-1)+1)
#define swap(a, b) \
	do {\
		int __t = a;\
		a = b;\
		b = __t;\
	} while (0)

int main()
{
	int second;
	int row, col;
	int n;

	while (scanf("%d", &second), second != 0) {
		n = floor((1.0+sqrt(4.0*second-3.0))/2.0-1e-9);

		if (second-f(n) >= n) {
			col = n + 1;
			row = second - f(n) - n + 1;
		} else {
			col = n;
			row = n - (second - f(n));
		}
		if (n%2==0)
			swap(col, row);
		printf("%d %d\n", row, col);
	}
	return 0;
}

