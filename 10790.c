#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define C(n) ((n)*((n)-1)/2)

int main()
{
	int n, m;
	int round = 1;
	int64_t ans;

	while (scanf("%d%d", &m, &n), m||n) {
		ans = (int64_t)C(m)*(int64_t)C(n);
		printf("Case %d: %ld\n", round++, ans);
	}
	return 0;
}
