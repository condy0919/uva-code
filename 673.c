#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char stack[256];
int sp;

int main()
{
	int n;
	char str[256];
	int i;
	int flag;

	scanf("%d", &n);
	getchar();
	while (n-- > 0) {
		fgets(str, sizeof(str), stdin);
		str[strlen(str) - 1] = '\0';
		if (str[0] == '\0') {
			puts("Yes");
			continue;
		}

		sp = 0;
		flag = 0;
		if (strlen(str) % 2 == 1) {
			puts("No");
			continue;
		}

		for (i = 0; i < strlen(str); ++i) {
			if (str[i] == '(' || str[i] == '[')
				stack[sp++] = str[i];
			else if (str[i] == ')' || str[i] == ']') {
				if (sp == 0) {
					flag = 1;
					break;
				} else if ((str[i] == ')' && stack[sp-1] != '(') || (str[i] == ']' && stack[sp-1] != '[')) {
					flag = 1;
					break;
				} else
					--sp;
			}
		}
		if (flag == 0 && sp == 0)
			puts("Yes");
		else
			puts("No");
	}
	return 0;
}

