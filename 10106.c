#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4096

typedef struct bignum_t {
	int val[N];
	int len;
} bignum_t;

char str1[N], str2[N];
bignum_t a, b;
bignum_t ans;

void str2bignum(char* s, int len, bignum_t* pn)
{
	int i;
	for (i = len - 1; i >= 0; --i)
		pn->val[len - 1 - i] = s[i] - '0';
	pn->len = len;
}

void clean(bignum_t* pn)
{
	while (pn->len > 0 && pn->val[pn->len - 1] == 0)
		--pn->len;
}

void mul(bignum_t* ans, bignum_t* a, bignum_t* b)
{
	int i, j;

	memset(ans->val, 0, sizeof(int)*N);
	for (i = 0; i < a->len; ++i)
		for (j = 0; j < b->len; ++j)
			ans->val[i+j] += a->val[i] * b->val[j];
	for (i = 0; i < a->len + b->len - 1; ++i) {
		ans->val[i+1] += ans->val[i] / 10;
		ans->val[i] %= 10;
	}
	if (ans->val[i] == 0)
		--i;
	ans->len = i + 1;
}

void print_bignum(bignum_t* pn)
{
	int i;
	for (i = pn->len - 1; i >= 0; --i)
		printf("%c", pn->val[i] + '0');
}

int main()
{
	while (scanf("%s %s", str1, str2) == 2) {
		str2bignum(str1, strlen(str1), &a);
		str2bignum(str2, strlen(str2), &b);
		clean(&a);
		clean(&b);
		mul(&ans, &a, &b);
		clean(&ans);

		if (ans.len == 0)
			printf("0\n");
		else {
			print_bignum(&ans);
			putchar('\n');
		}
	}
	return 0;
}

