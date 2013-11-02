#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define pi (4*atan(1.0))

double solve(double B, double H)
{
	double h;
	double sum = 0;
	double theta;
	double r;
	
	while (1) {
		theta = atan(2.0*H/B);
		r = tan(theta/2.0) * B/2.0;
		if (r < 1e-6)
			break;

		sum += 2*pi*r;
		h = H - 2*r;
		B = B*h/H;
		H = h;
	}
	return sum;
}

int main()
{
	int total_test;
	double B, H;
	double ans;

	scanf("%d", &total_test);
	while (total_test-- > 0) {
		scanf("%lf%lf", &B, &H);
		printf("%13.6lf\n", solve(B, H));
		if (total_test)
			putchar('\n');
	}
	return 0;
}

