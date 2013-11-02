#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{
	int total_test;
	int row, col;
	int ans;

	scanf("%d", &total_test);
	while (total_test-- > 0) {
		scanf("%d%d", &row, &col);
		ans = ceil((row-2)/3.0) * ceil((col-2)/3.0);
		printf("%d\n", ans);
	}
	return 0;
}
