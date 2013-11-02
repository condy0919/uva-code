#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int convert(char* s, int len)
{
	int i;
	int rate = 2;
	int ret = 0;

	for (i = len - 1; i >= 0; --i) {
		ret += (s[i] - '0')* (rate - 1);
		rate *= 2;
	}
	return ret;
}

int main()
{
	char str[64];
	int ans;

	while (scanf("%s", str) == 1 && str[0] != '0') {
		ans = convert(str, strlen(str));
		printf("%d\n", ans);
	}
	return 0;
}

