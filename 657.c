#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * 不知道为什么这样就能AC，而用vis数组标记就不行.
 */

int rows, cols;
char map[50+2][50+2];
int store[1000];
int idx;

static int dx[] = {-1, 0, 1, 0},
		   dy[] = {0, 1, 0, -1};

int valid(int x, int y)
{
	if (x < 0 || x >= rows || y < 0 || y >= cols)
		return 0;
	return 1;
}

int cmp(const void* a, const void* b)
{
	return *(int*)a - *(int*)b;
}

void internal_dfs(int x, int y)
{
	int dir;
	int _x, _y;

	map[x][y] = '*';
	for (dir = 0; dir < 4; ++dir) {
		_x = x + dx[dir];
		_y = y + dy[dir];
		if (!valid(_x, _y) || map[_x][_y] != 'X')
			continue;
		internal_dfs(_x, _y);
	}
}

void dfs(int x, int y)
{
	int dir;
	int _x, _y;

	map[x][y] = '.';
	for (dir = 0; dir < 4; ++dir) {
		_x = x + dx[dir];
		_y = y + dy[dir];
		if (!valid(_x, _y) || map[_x][_y] == '.')
			continue;
		if (map[_x][_y] == 'X') {
			internal_dfs(_x, _y);
			++store[idx];
		}
		if (map[_x][_y] == '*')
			dfs(_x, _y);
	}
}

int main()
{
	int i, j;
	int round = 0;

	while (scanf("%d%d", &cols, &rows) && rows && cols) {
		memset(store, 0, sizeof(store));
		memset(map, 0, sizeof(map));
		idx = 0;
		getchar();
		for (i = 0; i < rows; ++i, getchar())
			for (j = 0; j < cols; ++j)
				map[i][j] = getchar();
		for (i = 0; i < rows; ++i)
			for (j = 0; j < cols; ++j)
				if (map[i][j] == '*') {
					dfs(i, j);
					++idx;
				}
		qsort(store, idx, sizeof(int), cmp);
		printf("Throw %d\n", ++round);
		for (i = 0; i < idx - 1; ++i)
			printf("%d ", store[i]);
		printf("%d\n\n", store[i]);
	}
	return 0;
}
