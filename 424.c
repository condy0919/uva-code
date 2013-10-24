#include <stdio.h>
#include <string.h>

#define BASE 10000
#define GAP 4


typedef struct bignum_t {
	int len;
	int val[100];
} bignum_t;

bignum_t add(bignum_t* a, bignum_t* b)
{
	bignum_t ret = { 0 };
	int i, j;

	if (a->len > b->len) {
		bignum_t* t = a;
		a = b;
		b = t;
	}

	for (i = 0; i < a->len; ++i) {
		ret.val[i] += a->val[i] + b->val[i];
		ret.val[i + 1] = (ret.val[i] / BASE);
		ret.val[i] %= BASE;
	}

	while (i < b->len) {
		ret.val[i] += b->val[i];
		ret.val[i + 1] += (ret.val[i] / BASE);
		ret.val[i] %= BASE;
		++i;
	}

	j = i + (ret.val[i] != 0);
	ret.len = j;
	return ret;
}

void reverse(char a[], int n)
{
	int i, j;
	for (i = 0, j = n -1; i < j; ++i, --j) {
		char t = a[i];
		a[i] = a[j];
		a[j] = t;
	}
}

int str2int(char a[], int pos, int len)
{
	int i;
	int ret = 0;
	int rate = 1;

	for (i = 0; i < len; ++i, rate *= 10)
		ret += rate * (a[i + pos] - '0');
	return ret;
}

void scan_d(bignum_t* a, char* str, int n)
{
	char temp[100] = {0};
	int i, j = 0;
	
	strcpy(temp, str);
	reverse(temp, n);

	for (i = 0; i < n - GAP; i += GAP)
		a->val[j++] = str2int(temp, i, 4);
	a->val[j++] = str2int(temp, i, n - i);
	a->len = j;
}

void print_bignum(bignum_t* a)
{
	int i;
	
	i = a->len - 1;
	printf("%d", a->val[i]);
	for (i = a->len - 2; i >= 0; --i)
		printf("%0*d", GAP, a->val[i]);
	putchar('\n');
}

int main()
{
	char str[100+1];
	bignum_t sum = {0}, v;

	while (scanf("%s", str), strcmp(str, "0") != 0) {
		scan_d(&v, str, strlen(str));
		sum = add(&sum, &v);
	}
	print_bignum(&sum);
	return 0;
}
