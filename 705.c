#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * 刚开始看这道题目，一点思路没有。一看网上的做法，顿时恍然大悟。
 * 原来是将图放大2倍或3倍。这个没有想到啊。。。
 */

#define N 256

char maze[N][N];
int row, col;
int max, circle_num, n;

void translate(int x, int y, int ch)
{
	int x_p = 3 * x, y_p = 3 * y;

	if (ch == '\\') {
		maze[x_p+0][y_p+0] = 1;
		maze[x_p+1][y_p+1] = 1;
		maze[x_p+2][y_p+2] = 1;
	} else if (ch == '/') {
		maze[x_p+0][y_p+2] = 1;
		maze[x_p+1][y_p+1] = 1;
		maze[x_p+2][y_p+0] = 1;
	}
}

int valid(int x, int y)
{
	if (x < 0 || x >= 3 * row)
		return 0;
	if (y < 0 || y >= 3 * col)
		return 0;
	return 1;
}

int dfs(int x, int y)
{
	static int dx[] = {-1, 0, 1, 0},
			   dy[] = {0, 1, 0, -1};
	int i;
	int _x, _y;

	++n;
	maze[x][y] = 2;
	for (i = 0; i < 4; ++i) {
		_x = x + dx[i];
		_y = y + dy[i];
		if (!valid(_x, _y) || maze[_x][_y] == -1) {
			maze[x][y] = -1;
			return 0;
		}
		/* obstacle or visited block */
		if (maze[_x][_y] != 1 && maze[_x][_y] != 2)
			if (dfs(_x, _y) == 0) {
				maze[x][y] = -1;
				return 0;
			}
	}
	return 1;
}

int main()
{
	int i, j;
	int ch;
	int round = 0;

	while (scanf("%d%d", &col, &row), row || col) {
		getchar();
		memset(maze, 0, sizeof(maze));
		max = 0;
		circle_num = 0;
		for (i = 0; i < row; ++i, getchar())
			for (j = 0; j < col; ++j)
				translate(i, j, getchar());
		for (i = 0; i < 3 * row; ++i)
			for (j = 0; j < 3 * col; ++j)
				if (maze[i][j] != 1 && maze[i][j] != 2 && maze[i][j] != -1) {
					n = 0;/* store reachable blocks */
					if (dfs(i, j)) {
						++circle_num;
						if (n > max)
							max = n;
					}
				}
		printf("Maze #%d:\n", ++round);
		if (max == 0)
			puts("There are no cycles.\n");
		else
			printf("%d Cycles; the longest has length %d.\n\n", circle_num, max / 3);
		
	}
	return 0;
}
