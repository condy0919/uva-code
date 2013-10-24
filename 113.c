#include <stdio.h>
#include <math.h>

int main()
{
	int n;
	double p, k;

	while (scanf("%d %lf", &n, &p) == 2) {
		k = pow(p, 1.0/n);
		printf("%.0lf\n", k);
	}

	return 0;
}
