#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char lines[1000000][200];
int n;

int cmp(const void* a, const void* b)
{
	return strcmp((const char*)a, (const char*)b);
}

int main()
{
	int ch;
	int i, j;
	int k = 0;

	while ((ch = getchar()) != EOF) {
		if (isalpha(ch))
			lines[n][k++] = tolower(ch);
		else if (k != 0) {
			lines[n++][k] = '\0';
			k = 0;
		}
	}

	qsort(lines, n, 200, cmp);

	printf("%s\n", lines[0]);
	for (i = 0, j = 1; j < n; ++i, ++j)
		if (strcmp(lines[i], lines[j]) != 0)
			printf("%s\n", lines[j]);

}
