#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct xy_t {
	char ch;
	int x, y;
} xy_t;

int n;
xy_t pool[15];
xy_t max_point[3];

void swap(char* a, char* b)
{
	char _t = *a;
	*a = *b;
	*b = _t;
}

double s(int i, int j, int k)
{
	double ret = fabs((pool[k].y-pool[i].y)*(pool[j].x-pool[i].x) - (pool[j].y-pool[i].y)*(pool[k].x-pool[i].x));
	return ret/2.0;
}

char internal(int i, int j, int k, int p)
{
	double s1, s2;

	s1 = s(i, j, k);
	s2 = s(p, i, j)+s(p, j, k)+s(p, k, i);
	if ((fabs(s1-s2) < 1e-6))
		return 1;
	return 0;
}

char no_internal_point(int i, int j, int k)
{
	int t;
	double square = s(i, j, k);

	for (t = 0; t < n; ++t) {
		if (t==i || t==j || t==k)
			continue;
		if (internal(i, j, k, t))
			return 0;
	}
	return 1;
}


void calc()
{
	int i, j, k;
	double max = 0;

	for (i = 0; i < n; ++i)
		for (j = i + 1; j < n; ++j)
			for (k = j + 1; k < n; ++k) {
				if (no_internal_point(i, j, k) && s(i, j, k) > max) {
					max = s(i, j, k);
					max_point[0] = pool[i];
					max_point[1] = pool[j];
					max_point[2] = pool[k];
				}
			}
}

void show()
{
	static char str[4] = {0};
	str[0] = max_point[0].ch;
	str[1] = max_point[1].ch;
	str[2] = max_point[2].ch;
	printf("%s\n", str);
}

int main()
{
	int i;
	
	while (scanf("%d", &n), n) {
		getchar();
		for (i = 0; i < n; ++i, getchar())
			scanf("%c %d%d", &pool[i].ch, &pool[i].x, &pool[i].y);
		calc();
		show();
	}
	return 0;
}

