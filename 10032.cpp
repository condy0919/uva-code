#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

int n;
int weight[100];
int ans[2], _min;

void dfs(int cur, int p1, int w1, int p2, int w2)
{
	if (cur == n) {
		if (abs(p1 - p2) <= 1 && abs(w1 - w2) < _min) {
			_min = abs(w1 - w2);
			ans[0] = w1, ans[1] = w2;
		}
		return;
	}
	// prune
	if (n - cur < abs(p1 - p2) - 1)
		return;

	dfs(cur + 1, p1 + 1, w1 + weight[cur], p2, w2);
	dfs(cur + 1, p1, w1, p2 + 1, w2 + weight[cur]);
}

int main()
{
	int test_case;

	cin >> test_case;
	while (test_case-- > 0) {
		cin >> n;
		for (int i = 0; i < n; ++i)
			cin >> weight[i];
		_min = INT_MAX;
		dfs(0, 0, 0, 0, 0);
		if (ans[0] < ans[1])
			cout << ans[0] << " " << ans[1] << endl;
		else
			cout << ans[1] << " " << ans[0] << endl;
		if (test_case)
			cout << endl;
	}
	return 0;
}
