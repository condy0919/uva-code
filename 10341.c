#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define eps 1e-6

double p, q, r, s, t, u;

/*
 * monotonic decreasing
 */
double f(double x)
{
	return p*exp(-x) + q*sin(x) + r*cos(x) + s*tan(x) + t*x*x + u;
}

int main()
{
	while (scanf("%lf %lf %lf %lf %lf %lf", &p, &q, &r, &s, &t, &u) == 6) {
		double lo = 0, hi = 1;
		double mid = (lo + hi) / 2;
		if (f(1.0) > 0 || f(0) < 0) {
			puts("No solution");
			continue;
		}
		double res;
		while (res = f(mid), fabs(res) > eps) {
			if (res <= 0)
				hi = mid;
			else
				lo = mid;
			mid = (lo + hi) / 2;
		}
		printf("%.4lf\n", mid);
	}
	return 0;
}
