#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

int N;
char maze[4][4];
bool vis[4][4];
int _max, cnt;

bool can_place(int row, int col)
{
	for (int i = col - 1; i >= 0 && maze[row][i] == '.'; --i)
		if (vis[row][i])
			return false;
	for (int j = row - 1; j >= 0 && maze[j][col] == '.'; --j)
		if (vis[j][col])
			return false;
	return maze[row][col] == '.';
}

void dfs(int row, int col)
{
	bool flag = false;
	if (row == N) {
		_max = max(_max, cnt);
		return;
	}

	for (int i = col; i < N; ++i)
		if (can_place(row, i)) {
			flag = true;
			// set rook
			vis[row][i] = true;
			++cnt;
			if (i + 1 == N)
				dfs(row + 1, 0);
			else
				dfs(row, i + 1);
			--cnt;
			vis[row][i] = false;

			// not set rook
			if (i + 1 == N)
				dfs(row + 1, 0);
			else
				dfs(row, i + 1);
		}
	if (!flag)
		dfs(row + 1, 0);
}

int main()
{
	while (cin >> N, N) {
		getchar();
		memset(maze, 0, sizeof(maze));
		memset(vis, 0, sizeof(vis));
		_max = 0;
		cnt = 0;
		for (int i = 0; i < N; ++i, getchar())
			for (int j = 0; j < N; ++j)
				maze[i][j] = getchar();
		dfs(0, 0);
		cout << _max << endl;
	}
	return 0;
}
