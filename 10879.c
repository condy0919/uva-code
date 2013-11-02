#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int ans[4];
int ans_sp;

int main()
{
	int total_test;
	int round;
	int n;
	int i;

	scanf("%d", &total_test);
	for (round = 0; round < total_test; ++round) {
		scanf("%d", &n);
		printf("Case #%d: %d = ", round+1, n);

		ans_sp = 0;
		for (i = 2; ans_sp < 4; ++i)
			if (n % i == 0) {
				ans[ans_sp++] = i;
				ans[ans_sp++] = n / i;
			}
		printf("%d * %d = %d * %d\n", ans[0], ans[1], ans[2], ans[3]);
	}
	return 0;
}

