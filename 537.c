#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

double parse(char* s)
{
	int ret1 = 0;
	double ret;
	double rate = 0.1;
	int leap = 0;

	while (isdigit(*s)) {
		ret1 = 10 * ret1 + (*s - '0');
		++s;
	}

	if (*s == '.')
		++s;
	ret = ret1;
	while (isdigit(*s)) {
		ret += (*s - '0') * rate;
		++s;
		rate /= 10.0;
	}

	if (*s == 'm')
		ret *= 0.001;
	else if (*s == 'M')
		ret *= 1000000;
	else if (*s == 'k')
		ret *= 1000;

	return ret;
}


int main()
{
	char s[1024];
	double u, i, p;
	int is_u, is_i, is_p;
	int k, total_test;
	int pos;

	scanf("%d", &total_test);
	getchar();

	for (k = 0; k < total_test; ++k) {
		is_u = is_i = is_p = 0;
		fgets(s, sizeof(s), stdin);

		printf("Problem #%d\n", k + 1);

		pos = strchr(s, '=') - s;
		if (s[pos - 1] == 'U') {
			is_u = 1;
			u = parse(s + pos + 1);
		} else if (s[pos - 1] == 'P') {
			is_p = 1;
			p = parse(s + pos + 1);
		} else if (s[pos - 1] == 'I') {
			is_i = 1;
			i = parse(s + pos + 1);
		}

		pos = strchr(s + pos + 1, '=') - s;
		if (s[pos - 1] == 'U') {
			is_u = 1;
			u = parse(s + pos + 1);
		} else if (s[pos - 1] == 'P') {
			is_p = 1;
			p = parse(s + pos + 1);
		} else if (s[pos - 1] == 'I') {
			is_i = 1;
			i = parse(s + pos + 1);
		}

		if (!is_u) {
			u = p / i;
			printf("U=%.2fV\n", u);
		} else if (!is_i) {
			i = p / u;
			printf("I=%.2fA\n", i);
		} else {
			p = i * u;
			printf("P=%.2fW\n", p);
		}
		printf("\n");
	}

	return 0;
}
