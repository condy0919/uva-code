#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

typedef struct point_t {
	int x;
	int y;
	int z;
} point_t;

#define eps (1e-6)

int diff[10];
point_t p[5000];
int sp=0;

double d(point_t a, point_t b)
{
	double ret;

	ret = (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z);
	ret = sqrt(ret);

	return (int)(ret+eps);
}

int main()
{
	int x, y, z;
	int i, j;
	int min;
	int dis;

	while (scanf("%d%d%d", &x, &y, &z), x||y||z) {
		p[sp].x = x;
		p[sp].y = y;
		p[sp].z = z;
		++sp;
	}
	for (i = 0; i < sp; ++i) {
		min = 0x7fffffff;
		for (j = 0; j < sp; ++j) {
			if (i == j)
				continue;
			dis = d(p[i], p[j]);
			if (dis < min)
				min=dis;
		}
		diff[min]++;
	}
	for (i = 0; i < 10; ++i)
		printf("%4d", diff[i]);
	puts("");
	return 0;
}
