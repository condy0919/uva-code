#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char keyword[20][20+1];
char excuse[20][70+1];
char origion[20][70+1];
int match[20];
int k, e;

int find_max(int a[], int n)
{
	int m = a[0];
	int i;

	for (i = 1; i < n; ++i)
		if (m < a[i])
			m = a[i];
	return m;
}

void show_excuse(int match[], int m, char (*excuse)[70+1], int n)
{
	int i;

	for (i = 0; i < n; ++i)
		if (match[i] == m)
			printf("%s\n", excuse[i]);
}

void process()
{
	int i, j;
	int pos;
	char* p;
	int time;
	int case1, case2;

	for (i = 0; i < e; ++i) {
		time = 0;
		for (j = 0; j < k; ++j) {
			p = excuse[i];

			while ((p = strstr(p, keyword[j])) != NULL) {
				case1 = case2 = 0;

				pos = p - excuse[i];

				if (pos == 0 || !isalpha(excuse[i][pos - 1]))
					case1 = 1;

				pos += strlen(keyword[j]);
				p += strlen(keyword[j]);
				if (pos == strlen(excuse[i]) || !isalpha(excuse[i][pos]))
					case2 = 1;
				if (case1 && case2)
					++time;
			}
		}
		match[i] = time;
	}
}

int main()
{
	int i, j;
	int round = 0;
	int max;

	while (scanf("%d%d", &k, &e) == 2) {
		for (i = 0; i < k; ++i)
			scanf("%s", keyword[i]);
		for (i = 0; i < k; ++i)
			for (j = 0; keyword[i][j]; ++j)
				keyword[i][j] = tolower(keyword[i][j]);

		getchar();
		for (i = 0; i < e; ++i, getchar())
			scanf("%[^\n]", origion[i]);
		for (i = 0; i < e; ++i)
			for (j = 0; origion[i][j]; ++j)
				excuse[i][j] = tolower(origion[i][j]);

		memset(match, 0, sizeof(match));
		printf("Excuse Set #%d\n", ++round);

		process();
		max = find_max(match, e);
		show_excuse(match, max, origion, e);
		printf("\n");
	}

	return 0;
}

