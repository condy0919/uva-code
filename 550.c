#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main()
{
	int base, c, b;
	int a;
	int i;
	int carry;

	while (scanf("%d%d%d", &base, &c, &b) == 3) {
		a = c;
		carry = 0;
		for (i = 0; 1; ++i) {
			int t = (a * b + carry) /* *(int)pow(base, i)*/;
			carry = t / base;
			a = t % base;
			/* carry = t / (int)pow(base, i + 1); */
			/* a = t % (int)pow(base, i + 1) / (int)pow(base, i); */
			if (carry == 0 && a == c)
				break;
		}
		printf("%d\n", i + 1);
	}

	return 0;
}
