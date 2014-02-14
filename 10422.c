#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 又惯性思维，碰到最短的就直接想到了BFS，没有想到还可以转化为DFS来做，而且这样做更
 * 省空间。
 * http://blog.csdn.net/frankiller/article/details/7839423
 */

int a[5][5], goal[5][5] = {
	{1,1,1,1,1}, {0,1,1,1,1}, {0,0,2,1,1}, {0,0,0,0,1}, {0,0,0,0,0}
};
const int dx[] = {-2,-2,-1,1,-1,1,2,2}, dy[] = {-1,1,2,2,-2,-2,-1,1};
int min;

void find_space(int* px, int* py)
{
	int i, j;
	for (i = 0; i < 5; ++i)
		for (j = 0; j < 5; ++j)
			if (a[i][j] == 2) {
				*px = i, *py = j;
				return;
			}
}

void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

void dfs(int x, int y, int moves, int prev)
{
	int diff = 0, i, j, dir;
	int _x, _y;

	if (moves >= min)
		return;

	for (i = 0; i < 5; ++i)
		for (j = 0; j < 5; ++j)
			if (a[i][j] != goal[i][j])
				++diff;
	if (diff == 0) {
		min = moves;
		return;
	} else if (diff / 2 + moves >= min)/* 这一处剪枝我是没有想到啊。 */
		return;

	for (dir = 0; dir < 8; ++dir) {
		_x = x + dx[dir], _y = y + dy[dir];
		/* dir为当前的方向，而prev为上一次所用的方向，如果它们是相反方向，就不用了. */
		if (_x < 0 || _x >= 5 || _y < 0 || _y >= 5 || dir + prev == 7)
			continue;
		swap(&a[x][y], &a[_x][_y]);
		dfs(_x, _y, moves + 1, dir);
		swap(&a[x][y], &a[_x][_y]);
	}
}

int main()
{
	int cases;
	int i, j;
	char s[6];
	int x0, y0;

	scanf("%d\n", &cases);
	while (cases-- > 0) {
		for (i = 0; i < 5; ++i) {
			fgets(s, sizeof(s), stdin); getchar();
			for (j = 0; j < 5; ++j)
				if (s[j] == '1')
					a[i][j] = 1;
				else if (s[j] == '0')
					a[i][j] = 0;
				else 
					a[i][j] = 2;
		}
		min = 11;
		find_space(&x0, &y0);
		dfs(x0, y0, 0, 8);
		if (min == 11)
			puts("Unsolvable in less than 11 move(s).");
		else
			printf("Solvable in %d move(s).\n", min);
	}
	return 0;
}
