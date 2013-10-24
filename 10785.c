#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* vowel = "AUEOI";
const char* consonants = "JSBKTCLDMVNWFXGPYHQZR";

char pre_vowel[105];
char pre_cons[105];
char v[105], c[105];

int cmp(const void* a, const void* b)
{
	return *(char*)a - *(char*)b;
}

int main()
{
	int total_test, round;
	int len;
	int i, j, k;

	for (i = 0; i < 211/2; ++i)
		pre_vowel[i] = vowel[i/21];
	for (i = 0; i < 211/2; ++i)
		pre_cons[i] = consonants[i/5];

	scanf("%d", &total_test);
	for (round = 0; round < total_test; ++round) {
		scanf("%d", &len);
		printf("Case %d: ", 1 + round);

		j = k = 0;
		for (i = 0; i < len; ++i) {
			if ((i + 1) % 2 == 1) { /* odd */
				v[j] = pre_vowel[j];
				++j;
			} else {
				c[k] = pre_cons[k];
				++k;
			}
		}
		qsort(v, j, sizeof(char), cmp);
		qsort(c, k, sizeof(char), cmp);
		for (i = j = k = 0; i < len; ++i) {
			if ((i + 1) % 2 == 1)
				putchar(v[j++]);
			else
				putchar(c[k++]);
		}
		putchar('\n');
	}

	return 0;
}

