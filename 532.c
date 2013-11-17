#include <stdio.h>
#include <string.h>

/*
 * 奇葩之极的题目。
 * 本来写的标准的BFS（C++），可惜超时了。
 * 于是改用C写，发现会莫明奇妙的RE。只能用C改写网上正确的程序了。。。
 */

#define N 29800

typedef struct elem_t {
	int x, y, z, d;
} elem_t;

const int dir[6][3] = {
	{-1, 0, 0},
	{1, 0, 0},
	{0, -1, 0},
	{0, 1, 0},
	{0, 0, -1},
	{0, 0, 1}
};

elem_t Q[N];
int head, tail;
int L, R, C;
char maze[40][40][40];
char vis[40][40][40];
elem_t S, E;
elem_t e, t;
char s[40];
int min;

void bfs()
{
	int head = 0, tail = 1;
	int hx, hy, hz;
	int i;

	Q[0].x = S.x;
	Q[0].y = S.y;
	Q[0].z = S.z;
	vis[S.x][S.y][S.z] = 1;
	while (head < tail) {
		for (i = 0; i < 6; ++i) {
			hx = Q[head].x + dir[i][0];
			hy = Q[head].y + dir[i][1];
			hz = Q[head].z + dir[i][2];
			if (0<=hx&&hx<L && 0<=hy&&hy<R && 0<=hz&&hz<C && maze[hx][hy][hz] && !vis[hx][hy][hz]) {
				if (hx == E.x && hy == E.y && hz == E.z) {
					min = Q[head].d + 1;
					return;
				}
				Q[tail].x = hx;
				Q[tail].y = hy;
				Q[tail].z = hz;
				Q[tail++].d = Q[head].d + 1;
				vis[hx][hy][hz] = 1;
			}
		}
		head++;
	}
}

int main()
{
	int i, j, k;
	int _x, _y, _z;
	int trapped;

	while (scanf("%d%d%d", &L, &R, &C) == 3) {
		if (L == 0 && R == 0 && C == 0)
			break;
		getchar();
		memset(vis, 0, sizeof(vis));
		memset(maze, 0, sizeof(maze));
		
		for (i = 0; i < L; ++i)
			for (j = 0; j < R; ++j) {
				scanf("%s", s);
				for (k = 0; k < C; ++k)
					if (s[k] == 'S') {
						S.x = i; S.y = j; S.z = k; S.d = 0;
					} else if (s[k] == 'E') {
						E.x = i; E.y = j; E.z = k;
						maze[i][j][k] = 1;
					} else if (s[k] == '.')
						maze[i][j][k] = 1;
			}
		min = -1;
		bfs();
		if (min < 0)
			printf("Trapped!\n");
		else
			printf("Escaped in %d minute(s).\n",min);
	}

	return 0;
}
