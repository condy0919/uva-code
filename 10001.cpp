#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstring>

/*
 * 这次题目看得云里雾里。。。压根就不知道在讲什么。后来啊，看了mathworld上的图之后，
 * 总算理解了。。。但编码的时候又犯小错误了，由于符号优先级的问题，WA好多次。。。
 * 看来还是得细心啊。。。
 */

using namespace std;

int old_state[8][3] = {
	{0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1},
	{1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}
};
int new_state[8];

bool dfs(int pos, int target[], int ancestor[], int n)
{
	if (pos == n + 1)
		return ancestor[0] == ancestor[n] && ancestor[1] == ancestor[n + 1];

	for (int i = 0; i < 8; ++i)
		if (new_state[i] == target[pos]) {
			if (pos != 1 && (ancestor[pos - 1] != old_state[i][0] || ancestor[pos] != old_state[i][1]))
				continue;
			if (pos == 1) {
				ancestor[pos - 1] = old_state[i][0];
				ancestor[pos] = old_state[i][1];
			}
			ancestor[pos + 1] = old_state[i][2];
			if (dfs(pos + 1, target, ancestor, n))
				return true;
		}
	return false;
}

int main()
{
	int t, N;
	char str[33];
	int target[34], ancestor[34];

	while (cin >> t >> N >> str) {
		for (int i = 0; i < 8; ++i) {
			new_state[i] = t % 2;
			t /= 2;
		}
		for (int i = 0; i < N; ++i)
			target[i + 1] = str[i] - '0';
		if (dfs(1, target, ancestor, N))
			puts("REACHABLE");
		else
			puts("GARDEN OF EDEN");
	}
	return 0;
}
