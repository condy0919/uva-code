#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char passwd[1000];
char guess[1000];

void calc(int* a, int* b, int len)
{
	char passwd_visit[1000] = { 0 };
	char guess_visit[1000] = { 0 };
	int i, j;
	int na = 0, nb = 0;

	for (i = 0; i < len; ++i)
		if (passwd[i] == guess[i]) {
			++na;
			passwd_visit[i] = guess_visit[i] = 1;
		}

	for (i = 0; i < len; ++i) {
		if (passwd_visit[i])
			continue;

		for (j = 0; j < len; ++j) {
			if (guess_visit[j])
				continue;

			if (guess[j] == passwd[i]) {
				++nb;
				guess_visit[j] = passwd_visit[i] = 1;
				break;
			}
		}
	}
	*a = na;
	*b = nb;
}

int main()
{
	int len;
	int i;
	int a, b;
	int game = 0;

	while (scanf("%d", &len), len != 0) {
		for (i = 0; i < len; ++i)
			scanf("%d", &passwd[i]);

		printf("Game %d:\n", game+1);
		while (1) {
			for (i = 0; i < len; ++i)
				scanf("%d", &guess[i]);
			if (guess[0] == 0) {
				++game;
				break;
			}
			calc(&a, &b, len);
			printf("    (%d,%d)\n", a, b);
		}
	}

	return 0;
}
