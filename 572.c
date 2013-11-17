#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define VISITED 1

int rows, cols;
char map[100+3][100+3];

void dfs(int x, int y)
{
	static int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1}, 
			   dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
	int dir;
	int _x, _y;

	map[x][y] = VISITED;
	for (dir = 0; dir < 8; ++dir) {
		_x = x + dx[dir];
		_y = y + dy[dir];
		if (map[_x][_y] == '@')
			dfs(_x, _y);
	}
}

int main()
{
	int i, j;
	int cnt;

	while (scanf("%d%d", &rows, &cols), rows||cols) {
		getchar();
		memset(map, 0, sizeof(map));
		cnt = 0;
		for (i = 1; i <= rows; ++i, getchar())
			for (j = 1; j <= cols; ++j)
				map[i][j] = getchar();
		for (i = 1; i <= rows; ++i)
			for (j = 1; j <= cols; ++j)
				if (map[i][j] == '@') {
					dfs(i, j);
					++cnt;
				}
		printf("%d\n", cnt);
	}
	return 0;
}
