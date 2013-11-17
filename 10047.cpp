#include <iostream>
#include <queue>
#include <algorithm>
#include <cstdio>
#include <cstring>

/*
 * 从这题中，我终于知道了怎样写BFS才能速度最快啊。。
 * 以前一直的是速度比较慢的方法啊。。
 */

using namespace std;

enum { GREED, WHITE, BLUE, RED, BLACK };
enum { NORTH, EAST, SOUTH, WEST };

static int dx[] = {-1, 0, 1, 0},
		   dy[] = {0, 1, 0, -1};

struct elem_t {
	int x, y;
	int dir, color;
	int step;

	elem_t() {
		x = y = dir = color = step;
	}

	elem_t(int _x, int _y, int _d, int _c, int _s = 0) {
		x = _x; y = _y; dir = _d; color = _c; step = _s;
	}
};

elem_t S;
int M, N;
bool vis[25][25][5][4];
char maze[25][25];

int bfs()
{
	elem_t e;
	queue<elem_t> Q;

	Q.push(S);
	while (!Q.empty()) {
		e = Q.front(); Q.pop();

		if (maze[e.x][e.y] == 'T' && e.color == GREED)
			return e.step;
		vis[e.x][e.y][e.color][e.dir] = true;

		// turn left
		if (!vis[e.x][e.y][e.color][(e.dir-1+4)%4])
			Q.push(elem_t(e.x, e.y, (e.dir-1+4)%4, e.color, e.step + 1));

		// turn right
		if (!vis[e.x][e.y][e.color][(e.dir+1)%4])
			Q.push(elem_t(e.x, e.y, (e.dir+1)%4, e.color, e.step + 1));

		// forward
		int _x = e.x, _y = e.y;
		_x += dx[e.dir];
		_y += dy[e.dir];
		if (_x < 0 || _x >= M || _y < 0 || _y >= N || 
				maze[_x][_y] == '#' || vis[_x][_y][(e.color+1)%5][e.dir])
			continue;
		Q.push(elem_t(_x, _y, e.dir, (e.color+1)%5, e.step + 1));
	}
	return -1;
}

int main()
{
	int round = 0;

	while (cin >> M >> N, M || N) {
		cin.ignore();
		memset(maze, 0, sizeof(maze));
		memset(vis, 0, sizeof(vis));
		for (int i = 0; i < M; ++i, getchar())
			for (int j = 0; j < N; ++j) {
				int ch = getchar();
				maze[i][j] = ch;
				if (ch == 'S') {
					S.x = i; S.y = j; S.dir = NORTH; S.color = GREED; S.step = 0;
				}
			}
		int ans = bfs();
		if (round)
			cout << endl;
		cout << "Case #" << ++round << endl;
		if (ans == -1)
			cout << "destination not reachable" << endl;
		else
			cout << "minimum time = " << ans << " sec" << endl;
	}
	return 0;
}

