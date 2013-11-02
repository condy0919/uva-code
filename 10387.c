#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * 一开始思路都没有，看了网上的介绍之后才懂了。
 * 说一下原理.
 */

#define pi (4.0*atan(1.0))

int main()
{
	int a, b;
	int s;
	int m, n;
	double hl, vl;
	double theta, v;

	while (scanf("%d%d%d%d%d", &a,&b,&s,&m,&n),a||b||s||m||n) {
		vl = (double)n * (double)b;
		hl = (double)m * (double)a;
		v = sqrt(vl*vl+hl*hl)/s;
		theta = atan(vl/hl)/pi*180.0;
		printf("%.2lf %.2lf\n", theta, v);
	}
	return 0;
}
