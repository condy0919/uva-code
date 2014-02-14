#include <stdio.h>
#include <string.h>

/*
 * 暂时还没有好的trick，2s多一点，差点超时。。。
 */

#define VALUE(x) (ref[x])

int ref[128];
int val[128];

void init()
{
	ref['I'] = 1;
	ref['V'] = 5;
	ref['X'] = 10;
	ref['L'] = 50;
	ref['C'] = 100;
	ref['D'] = 500;
	ref['M'] = 1000;
}

int roman(const char* s)
{
	int ret = 0;
	int i, j;

	for (i = strlen(s) - 1; i >= 0; i = j) {
		ret += VALUE(s[i]);
		for (j = i - 1; j >= 0 && VALUE(s[j]) < VALUE(s[i]); --j)
			ret -= VALUE(s[j]);
	}
	return ret;
}

int a2i(char* s)
{
	int ret = 0, i;
	for (i = 0; i < strlen(s); ++i)
		ret = 10 * ret + val[s[i]];
	return ret;
}

void dfs(char s[3][10], int cur, int pos, int* ans)
{
	int start_number;
	int i;

	if (*ans > 1)
		return;
	if (cur == 3) {
		*ans += (a2i(s[0]) + a2i(s[1]) == a2i(s[2]));
		return;
	}
	if (pos == strlen(s[cur])) {
		dfs(s, cur + 1, 0, ans);
		return;
	}
	if (val[s[cur][pos]] != -1) {
		dfs(s, cur, pos + 1, ans);
		return;
	}

	start_number = (pos == 0) ? 1 : 0;
	for (i = start_number; i <= 9; ++i) {
		val[s[cur][pos]] = i;
		dfs(s, cur, pos + 1, ans);
		if (*ans > 1)
			return;
	}
	val[s[cur][pos]] = -1;/* resume */
}

int main()
{
	char s[3][10];
	int ra, rb, rr;
	int ans;
	int i;

	init();
	while (scanf("%[^+]+%[^=]=%s\n", s[0], s[1], s[2]) == 3) {
		for (i = 0; i < 128; ++i)
			val[i] = -1;
		ra = roman(s[0]);
		rb = roman(s[1]);
		rr = roman(s[2]);

		if (ra + rb == rr)
			printf("Correct ");
		else
			printf("Incorrect ");

		ans = 0;
		dfs(s, 0, 0, &ans);
		if (ans == 0)
			puts("impossible");
		else if (ans == 1)
			puts("valid");
		else
			puts("ambiguous");
	}
	return 0;
}
