#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

/*
 * 这题做了好久了。。。还是TLE。
 * 一开始的解法是从1开始，从它的邻接点一个一个递归下去。果断TLE了。
 * 然后就一直受到了惯性思维的影响，依然没有跳出这个圈。
 * 后来一看解题报告，原来这里的dfs不一定是要从邻接点开始的啊。。
 * http://blog.csdn.net/frankiller/article/details/7802812
 */

using namespace std;

#define WHITE false
#define BLACK true

bool G[101][101];
bool color[101];
int n, k;
vector<int> ans;

void dfs(int cur, vector<int>& bp)
{
	bool flag = true;

	if (cur == n + 1) {
		if (bp.size() > ans.size())
			ans = bp;
		return;
	}
	if (n - cur + 1 + bp.size() < ans.size())
		return;

	for (int i = 1; i <= n; ++i)
		if (G[cur][i] && color[i] == BLACK) {
			flag = false;
			break;
		}
	if (flag) {
		color[cur] = BLACK;
		bp.push_back(cur);
		dfs(cur + 1, bp);
		bp.pop_back();
		color[cur] = WHITE;
	}
	dfs(cur + 1, bp);
}

int main()
{
	int test_case;
	int x, y;
	vector<int> bp;

	cin >> test_case;
	while (test_case-- > 0) {
		memset(G, 0, sizeof(G));
		memset(color, WHITE, sizeof(color));
		ans.clear();
		cin >> n >> k;
		for (int i = 0; i < k; ++i) {
			cin >> x >> y;
			G[x][y] = G[y][x] = true;
		}
		dfs(1, bp);
		cout << ans.size() << endl;
		cout << ans[0];
		for (int i = 1; i < ans.size(); ++i)
			cout << " " << ans[i];
		cout << endl;
	}
	return 0;
}
