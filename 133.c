#include <stdio.h>
#include <stdlib.h>

#define NON_VISIABLE -1

int queue[20];
int size = 0;
int n;

void pop(int pos)
{
	queue[pos] = NON_VISIABLE;
	--size;
}

void left_move(int* p, int times)
{
	--times;
	while (queue[*p] == NON_VISIABLE)
		*p = (*p + 1) % n;
	while (times > 0) {
		if (queue[*p] != NON_VISIABLE)
			--times;
		*p = (*p + 1) % n;
	}
	while (queue[*p] == NON_VISIABLE)
		*p = (*p + 1) % n;
}

void right_move(int* p, int times)
{
	--times;
	while (queue[*p] == NON_VISIABLE)
		*p = (*p - 1 + n) % n;
	while (times > 0) {
		if (queue[*p] != NON_VISIABLE)
			--times;
		*p = (*p - 1 + n) % n;
	}
	while (queue[*p] == NON_VISIABLE)
		*p = (*p - 1 + n) % n;
}

int main()
{
	int k, m;
	int left, right;
	int first;
	int i;

	while (scanf("%d%d%d", &n, &k, &m), n||k||m) {
		size = n, left = 0, right = n - 1;
		first = 1;
		for (i = 0; i < n; ++i)
			queue[i] = i + 1;
		while (size > 0) {
			left_move(&left, k);
			right_move(&right, m);
			if (left == right) {
				if (first) {
					printf("%3d", queue[left]);
					first = 0;
				} else
					printf(",%3d", queue[left]);
				pop(left);
			} else {
				if (first) {
					printf("%3d%3d", queue[left], queue[right]);
					first = 0;
				} else
					printf(",%3d%3d", queue[left], queue[right]);
				pop(right);
				pop(left);
			}
		}
		putchar('\n');
	}
	return 0;
}

