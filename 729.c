#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 还是C版本的快啊。。。
 * 主要是去重复的问题。。。
 * 在递归时，若在当前位置遇到了已经在当前位置出现过的数学，则
 * 将其放弃。。
 * 例：AXXXA
 * 将后面的A交换至前面时，后面仍旧是XXXA，则再次调用perm必然会
 * 产生重复的排列。。。
 */

#define swap(a, b, t) \
	do {\
		(t) = (a);\
		(a) = (b);\
		(b) = (t);\
	} while (0)

void perm(int a[], int m, int n)
{
	int i, t;
	int vis[2] = {0};

	if (m == n) {
		for (i = 0; i < n; ++i)
			printf("%d", a[i]);
		puts("");
		return;
	}

	for (i = m; i < n; ++i) {
		if (vis[a[i]])
			continue;

		swap(a[i], a[m], t);
		perm(a, m + 1, n);
		swap(a[i], a[m], t);
		vis[a[i]] = 1;
	}
}

int main()
{
	int T, N, H;
	int i;
	int a[16] = {0};

	scanf("%d", &T);
	while (T-- > 0) {
		scanf("%d%d", &N, &H);
		for (i = N - 1; i > N - H - 1; --i)
			a[i] = 1;
		for (; i >= 0; --i)
			a[i] = 0;
		perm(a, 0, N);
		if (T)
			puts("");
	}
	return 0;
}
