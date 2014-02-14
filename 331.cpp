#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

int a[5], n;
int cnt;

bool in_order()
{
	for (int i = 0; i < n - 1; ++i)
		if (a[i] > a[i + 1])
			return false;
	return true;
}

void dfs()
{
	if (in_order()) {
		++cnt;
		return;
	}
	for (int i = 0; i < n - 1; ++i)
		if (a[i] > a[i + 1]) {
			swap(a[i], a[i + 1]);
			dfs();
			swap(a[i], a[i + 1]);
		}
}

int main()
{
	int round = 0;

	while (cin >> n, n) {
		cnt = 0;
		for (int i = 0; i < n; ++i)
			cin >> a[i];
		if (!in_order())
			dfs();
		printf("There are %d swap maps for input data set %d.\n", cnt, ++round);
	}
	return 0;
}
