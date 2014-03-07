#include <cstdio>
#include <algorithm>

using namespace std;

enum { HAPPY = 1, UNHAPPY };

int next(int x)
{
	int ret = 0, v;
	while (x > 0) {
		v = x % 10;
		ret += v * v;
		x /= 10;
	}
	return ret;
}

int is[729+1];
int happy(int x)
{
	if (x <= 729 && is[x])
		return is[x];
	if (happy(next(x)) == UNHAPPY) {
		if (x <= 729)
			is[x] = UNHAPPY;
		return UNHAPPY;
	}
	if (x <= 729)
		is[x] = HAPPY;
	return HAPPY;
}

void init()
{
	is[0] = is[2] = is[3] = is[4] = UNHAPPY;
	is[5] = is[6] = UNHAPPY;
	is[1] = is[7] = HAPPY;
}

int main()
{
	int T, v;
	scanf("%d", &T);
	init();
	for (int t = 0; t < T; ++t) {
		scanf("%d", &v);
		printf("Case #%d: %d %s number.\n", t + 1, v, 
				happy(v) == HAPPY ? "is a Happy" : "is an Unhappy");
	}
	return 0;
}
