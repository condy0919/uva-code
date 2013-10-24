#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	int n;
	double ans;

	while (scanf("%d", &n), n > 0) {
		if (n == 1) {
			printf("0%%\n");
		} else {
			ans = floor(n * 25.0 + 0.5);
			printf("%.0lf%%\n", ans);
		}
	}
	return 0;
}
