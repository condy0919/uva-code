#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double s;
double a1;

int main()
{
	int total_test;
	int n;
	int i;
	double a0, an_1;
	double c;
	
	scanf("%d", &total_test);
	while (total_test-- > 0) {
		scanf("%d", &n);
		scanf("%lf%lf", &a0, &an_1);

		s = 0.0;
		for (i = 1; i <= n; ++i) {
			scanf("%lf", &c);
			s += c * (n - i + 1);
		}
		s *= 2.0;
		
		a1 = (n*a0 - s + an_1)/(n+1);
		printf("%.2lf\n", a1);
		if (total_test)
			puts("");
	}

	return 0;
}

