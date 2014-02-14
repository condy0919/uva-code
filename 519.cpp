#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>

/*
 * 第一次自己想出剪枝的方法来。
 */

using namespace std;

#define N 6

const int JUT = 1, CAVITY = -1, FLAT = 0;
typedef int state_t[4];

inline int val(char ch) 
{
	if (ch == 'F')
		return FLAT;
	else if (ch == 'O')
		return JUT;
	return CAVITY;
}

int board[2 * N + 1][2 * N + 1];
state_t pieces[N * N];
bool vis[N * N];
int n;
int row, col;

bool place(int x, int y, int idx)
{
	static int dx[] = { -1, 0, 1, 0 }, dy[] = { 0, 1, 0, -1 };
	int _x, _y;

	x = 2 * x + 1;
	y = 2 * y + 1;
	for (int i = 0; i < 4; ++i) {
		_x = x + dx[i];
		_y = y + dy[i];
		board[_x][_y] += pieces[idx][i];
	}

	if (board[x - 1][y] != 0 || board[x][y - 1] != 0)
		return false;
	return true;
}

void remove(int x, int y, int idx)
{
	static int dx[] = { -1, 0, 1, 0 }, dy[] = { 0, 1, 0, -1 };
	int _x, _y;

	x = 2 * x + 1;
	y = 2 * y + 1;
	for (int i = 0; i < 4; ++i) {
		_x = x + dx[i];
		_y = y + dy[i];
		board[_x][_y] -= pieces[idx][i];
	}
}

inline bool reachable(int x, int y)
{
	return x >= 0 && x < row && y >= 0 && y < col;
}

void next_move(int x, int y, int& next_x, int& next_y, int& dir)
{
	const int dx[] = { 1, -1 }, dy[] = { -1, 1 };
	const int ddx[] = { 1, 0 }, ddy[] = { 0, 1 };// down and right
	int order[2] = { 0, 1 };
	int i;

	if (reachable(x + dx[dir], y + dy[dir])) {
		next_x = x + dx[dir];
		next_y = y + dy[dir];
		return;
	}

	if (dir == 1)
		swap(order[0], order[1]);

	for (i = 0; i < 2; ++i)
		if (reachable(x + ddx[order[i]], y + ddy[order[i]])) {
			next_x = x + ddx[order[i]];
			next_y = y + ddy[order[i]];
			break;
		}
	dir ^= 1;
}

int hash(int a[4])
{
	static int w[4] = { 1, 3, 9, 27 };
	int s = 0;
	for (int i = 0; i < 4; ++i)
		s += w[i] * (a[i] + 1);
	return s;
}

bool dfs(int x, int y, int cnt, int dir)
{
	int next_x, next_y;
	int t_dir;

	int failure[100];
	int len = 0;
	
	if (cnt == n)
		return true;

	for (int i = 0; i < n; ++i) {
		if (vis[i])
			continue;
		if (x == 0 && pieces[i][0] != FLAT || x == row - 1 && pieces[i][2] != FLAT)
			continue;
		if (y == 0 && pieces[i][3] != FLAT || y == col - 1 && pieces[i][1] != FLAT)
			continue;

		bool flag = false;
		for (int j = 0; j < len; ++j)
			if (hash(pieces[i]) == failure[j]) {
				flag = true;
				break;
			}
		if (flag)
			continue;

		if (x != 0 && x != row - 1 && y != 0 && y != col - 1)
			for (int j = 0; j < 4; ++j)
				if (pieces[i][j] == FLAT) {
					flag = true;
					break;
				}
		if (flag)
			continue;
			
		vis[i] = true;
		if (place(x, y, i)) {
			t_dir = dir;
			next_move(x, y, next_x, next_y, t_dir);
			if (dfs(next_x, next_y, cnt + 1, t_dir))
				return true;
			failure[len++] = hash(pieces[i]);
		}
		vis[i] = false;
		remove(x, y, i);
	}
	return false;
}

bool balance()
{
	int h_sum = 0, v_sum = 0;
	
	for (int i = 0; i < n; ++i) {
		h_sum += pieces[i][1] + pieces[i][3];
		v_sum += pieces[i][0] + pieces[i][2];
	}
	return h_sum == 0 && v_sum == 0;
}

int main()
{
	string s;
	int flat[4];

	while (cin >> row >> col, row != 0 && col != 0) {
		n = 0;
		memset(flat, 0, sizeof(flat));
		memset(vis, 0, sizeof(vis));
		memset(board, 0, sizeof(board));
		for (int i = 0; i < row * col; ++i) {
			cin >> s;
			for (int i = 0; i < 4; ++i) {
				pieces[n][i] = val(s[i]);
				if (s[i] == 'F')
					++flat[i];
			}
			++n;
		}
		
		if ((flat[0] != col || flat[2] != col || flat[1] != row || flat[3] != row) || !balance() || !dfs(0, 0, 0, 0))
			cout << "NO\n";
		else
			cout << "YES\n";
	}
	return 0;
}
