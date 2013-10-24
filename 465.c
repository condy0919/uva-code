#include <stdio.h>
#include <stdlib.h>

char num1[1024], num2[1024];
char op;
double a, b, ans;

const int limit = 0x7fffffff;

int main()
{
	while (scanf("%s %c %s", num1, &op, num2) == 3) {
		printf("%s %c %s\n", num1, op, num2);

		a = atof(num1);
		b = atof(num2);

		if (a > limit)
			printf("first number too big\n");
		if (b > limit)
			printf("second number too big\n");

		if (op == '+')
			ans = a + b;
		else
			ans = a * b;
		if (ans > limit)
			printf("result too big\n");
	}
	return 0;
}
