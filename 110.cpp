#include <iostream>
#include <algorithm>
#include <cstdio>

/*
 * 全排列的变化形式。。
 */

using namespace std;

char s[9] = "abcdefgh";

void print_chs(char s[], int n)
{
	putchar(s[0]);
	for (int i = 1; i < n; ++i)
		printf(",%c", s[i]);
}

void inverse(char s[], int st, int mid, int ed)
{
	reverse(s + st, s + mid);
	reverse(s + mid, s + ed);
	reverse(s + st, s + ed);
}

void perm(char s[], int m, int n, int shift)
{
	if (m == n) {
		printf("%*cwriteln(", shift * 2, ' ');
		print_chs(s, n);
		printf(")\n");
		return;
	}
	for (int i = m; i >= 0; --i) {
		if (i == m)
			printf("%*cif %c < %c then\n", 2 * shift, ' ', s[i - 1], s[m]);
		else if (i == 0)
			printf("%*celse\n", 2 * shift, ' ');
		else
			printf("%*celse if %c < %c then\n", 2 * shift, ' ', s[i - 1], s[m]);
		inverse(s, i, m, m + 1);
		perm(s, m + 1, n, shift + 1);
		inverse(s, i, i + 1, m + 1);
	}
}

int main()
{
	int T, N;

	cin >> T;
	while (T-- > 0) {
		cin >> N;

		printf("program sort(input,output);\nvar\n");
		print_chs(s, N);
		printf(" : integer;\nbegin\n  readln(");
		print_chs(s, N);
		printf(");\n");

		perm(s, 1, N, 1);

		printf("end.\n");
		if (T)
			putchar('\n');
	}
	return 0;
}
