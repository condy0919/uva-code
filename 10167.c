#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct xy_t {
	int x, y;
} xy_t;

xy_t points[50];
int sp;

int gcd(int A, int B)
{
	int r;

	while (B) {
		r = A % B;
		A = B;
		B = r;
	}
	return A;
}

int check(int A, int B)
{
	int i;
	int high = 0, low = 0;

	for (i = 0; i < sp; ++i)
		if (A * points[i].x + B * points[i].y > 0)
			++high;
		else if (A * points[i].x + B * points[i].y < 0)
			++low;
	return high == low;
}

int main()
{
	int N;
	int i;
	int x, y;
	int A, B;
	int ok;

	while (scanf("%d", &N), N) {
		sp = 0;
		ok = 0;

		for (i = 0; i < 2 * N; ++i) {
			scanf("%d%d", &x, &y);
			points[sp].x = x;
			points[sp].y = y;
			++sp;
		}

		for (A = -500; A <= 500; ++A) {
			for (B = -500; B <= 500; ++B) {
				if (gcd(abs(A), abs(B)) != 1)
					continue;
				if (check(A, B)) {
					ok = 1;
					break;
				}
			}
			if (ok)
				break;
		}
		if (ok)
			printf("%d %d\n", A, B);
	}
	return 0;
}
