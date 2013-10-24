#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define min(a, b) ((a) < (b) ? (a) : (b))

/*
 * 注意这里的边界条件是：
 * 当k=0时，为3. 1+2-3嘛。
 */

int solve(int k)
{
	double lower;
	int l;
	double m1, m2;

	lower = (-1 + sqrt(1 + 8.0*k))/2;
	l = ceil(lower);

	if (k % 2) {
		/* in the line y=4x+2 or y=4x+1 */
		if ((l-2) % 4 == 0 || (l - 1) % 4 == 0)
			return l;

		m1 = ceil((l-2)/ 4.0);
		m2 = ceil((l-1) / 4.0);
		return min(4*m1+2, 4*m2+1);
	}

	/* in the line y=4x-1 or y=4x */
	if ((l + 1) % 4 == 0 || l % 4 == 0)
		return l;

	m1 = ceil(l / 4.0);
	m2 = ceil((l + 1) / 4.0);
	return min(4*m1, 4*m2-1);
}

int main()
{
	int k;
	int total_test;
	int ans;

	scanf("%d", &total_test);
	while (total_test-- > 0) {
		scanf("%d", &k);
		if (k == 0)
			ans = 3;
		else
			ans = solve(abs(k));
		printf("%d\n", ans);
		if (total_test)
			putchar('\n');
	}
	return 0;
}

