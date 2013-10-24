#include <stdio.h>

int a[50];
int temp[50];

int merge(int a[], int st, int mid, int ed)
{
	int i, j, k;
	int ret = 0;

	for (i = 0; i <= mid - st; ++i)
		temp[i] = a[i + st];

	i = 0;
	j = mid + 1;
	k = st;
	while (i <= mid - st && j <= ed) {
		if (temp[i] < a[j]) {
			a[k++] = temp[i++];
		} else {
			ret += mid - st + 1 - i;
			a[k++] = a[j++];
		}
	}

	while (i <= mid - st)
		a[k++] = temp[i++];
	while (j <= ed)
		a[k++] = a[j++];

	return ret;
}

int merge_sort(int a[], int st, int ed)
{
	int ret1, ret2, ret3;
	int mid;

	if (st >= ed)
		return 0;

	mid = (st + ed) / 2;

	ret1 = merge_sort(a, st, mid);
	ret2 = merge_sort(a, mid + 1, ed);
	ret3 = merge(a, st, mid, ed);

	return ret1 + ret2 + ret3;
}

int main()
{
	int total_test;
	int n;
	int i;
	int ans;

	scanf("%d", &total_test);

	while (total_test-- > 0) {
		scanf("%d", &n);

		for (i = 0; i < n; ++i)
			scanf("%d", &a[i]);

		ans = merge_sort(a, 0, n - 1);
		printf("Optimal train swapping takes %d swaps.\n", ans);
	}
	return 0;
}
