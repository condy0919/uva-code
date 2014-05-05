#include <stdio.h>
#include <stdint.h>

#define MAXSIZE 31268

int s[MAXSIZE + 1] = {0}, incs[MAXSIZE + 1] = {0};
void init()
{
	int inc = 1, i;
	for (i = 1; i <= MAXSIZE; ++i) {
		if (i == 10 || i == 100 || i == 1000 || i == 10000)
			++inc;
		incs[i] = inc;
		s[i] += s[i - 1] + inc;
	}
}

char calc(int pos)
{
	int i;
	char __[10];
	for (i = 1; pos - s[i] > 0; ++i)
		pos -= s[i];
	for (i = 1; pos - incs[i] > 0; ++i)
		pos -= incs[i];
	sprintf(__, "%d", i);
	return __[pos - 1];
}

int main()
{
	int t, i;
	init();
	scanf("%d", &t);
	while (t-- > 0) {
		scanf("%d", &i);
		printf("%c\n", calc(i));
	}
	return 0;
}
