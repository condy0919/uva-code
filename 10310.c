#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct xy_t {
	double x, y;
} xy_t;

xy_t dog, gopher;
int n;
xy_t holes[1000];

inline double sqdis(double ax, double ay, double bx, double by)
{
	return (ax-bx)*(ax-bx)+(ay-by)*(ay-by);
}

int check(int i)
{
	double d1, d2;

	d1 = sqdis(holes[i].x, holes[i].y, gopher.x, gopher.y);
	d2 = sqdis(holes[i].x, holes[i].y, dog.x, dog.y);
	if (d1 * 4 < d2)
		return 1;
	return 0;
}

int main()
{
	int i, ok;

	while (scanf("%d", &n) == 1) {
		scanf("%lf%lf%lf%lf", &gopher.x, &gopher.y, &dog.x, &dog.y);
		ok = 0;
		for (i = 0; i < n; ++i)
			scanf("%lf%lf", &holes[i].x, &holes[i].y);
		for (i = 0; i < n; ++i)
			if (check(i)) {
				ok = 1;
				break;
			}
		if (ok)
			printf("The gopher can escape through the hole at (%.3lf,%.3lf).\n", holes[i].x, holes[i].y);
		else
			puts("The gopher cannot escape.");
	}
	return 0;
}
