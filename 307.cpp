#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cstring>

using namespace std;

/*
 * 一开始还是错，这可是我做过的题目啊。。。
 * 后来想了好久，终于发现原来是34,40行的vis[i]没有即时的set为false
 */

#define N 200

int n;
int a[N];
bool vis[N];
int sum, len, parts;

bool dfs(int depth, int idx, int remain)
{
	if (depth == parts - 1)
		return true;

	for (int i = idx; i < n; ++i) {
		if (vis[i] || a[i] > remain)
			continue;

		if (remain - a[i] == 0) {
			vis[i] = true;
			if (dfs(depth + 1, 0, len))
				return true;
			vis[i] = false;
			return false;
		} else {
			vis[i] = true;
			if (dfs(depth, i + 1, remain - a[i]))
				return true;
			vis[i] = false;
			if (remain == len)
				return false;
		}

		while (i + 1 < n && a[i] == a[i + 1])
			++i;
	}
	return false;
}

int main()
{
	while (cin >> n, n) {
		sum = 0;
		for (int i = 0; i < n; ++i) {
			cin >> a[i];
			sum += a[i];
		}
		sort(a, a + n, greater<int>());
		for (len = a[0]; len <= sum; ++len) {
			if (sum % len)
				continue;
			parts = sum / len;
			memset(vis, 0, sizeof(vis));
			if (dfs(0, 0, len)) {
				cout << len << endl;
				break;
			}
		}
	}
	return 0;
}
