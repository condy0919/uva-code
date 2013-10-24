#include <stdio.h>
#include <math.h>

#define s(n) ((1+n)*n/2)

int solve(int dis)
{
	int u, steps;
	int remain;
	int i;

	if (dis == 0)
		return 0;
	else if (dis == 1)
		return 1;
	else if (dis == 2)
		return 2;

	u = sqrt(dis);
	steps = 2 * (u - 1);
	remain = dis - u * (u - 1);

	for (i = u; remain != 0; --i)
		if (remain >= i) {
			steps += remain / i;;
			remain %= i;
		}
	return steps;
}

int main()
{
	int x, y;
	int total_test;
	int ans;
	
	scanf("%d", &total_test);
	while (total_test-- > 0) {
		scanf("%d%d", &x, &y);
		ans = solve(y - x);
		printf("%d\n", ans);
	}
	return 0;
}

