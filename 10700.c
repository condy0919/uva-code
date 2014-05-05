#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

/*
 * 竟然是精度的问题，int无法保存20^20
 */
typedef struct exp {
	char* s;
} exp;


/*
 * exp -> term '+ exp
 * term -> primary '* term
 */
int64_t primary(exp* p)
{
	int64_t ret = 0;
	while (isdigit(*p->s)) {
		ret = 10 * ret + (*p->s - '0');
		++p->s;
	}
	return ret;
}

int64_t term(exp* p, char high)
{
	int64_t ret = primary(p);
	while (*p->s == high) {
		++p->s;
		if (high == '*')
			ret *= primary(p);
		else
			ret += primary(p);
	}
	return ret;
}

int64_t calc(exp* p, char low, char high)
{
	int64_t ret = term(p, high);
	while (*p->s == low) {
		++p->s;
		if (low == '+')
			ret += term(p, high);
		else
			ret *= term(p, high);
	}
	return ret;
}

int main()
{
	int N;
	char s[300];
	exp e;

	scanf("%d", &N);
	while (N-- > 0) {
		int64_t _min, _max;

		scanf("%s", s);
		e.s = s;
		_min = calc(&e, '+', '*');
		e.s = s;
		_max = calc(&e, '*', '+');
		printf("The maximum and minimum are %lld and %lld.\n", _max, _min);
	}
	return 0;
}
