#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * 旋转90度
 */

int main()
{
	double x1,y1,x2,y2;
	double ox, oy;

	while (scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2) == 4) {
		if (x1 == x2 && y1 == y2) {
			printf("Impossible.\n");
			continue;
		}
		ox = (x1+x2)/2.0;
		oy = (y1+y2)/2.0;
		x1-=ox, y1-=oy;
		x2-=ox, y2-=oy;
		printf("%lf %lf %lf %lf\n", -y1+ox,x1+oy,-y2+ox,x2+oy);
	}
	return 0;
}

