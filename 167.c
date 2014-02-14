#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int G[8][8];
int prev_pos[8];
int val, _max;

int can_place(int row, int col)
{
	int i;
	for (i = 0; i < row; ++i)
		if (prev_pos[i] == col || 
				row - i == col - prev_pos[i] ||
				row - i == prev_pos[i] - col)
			return 0;
	return 1;
}

void dfs(int row)
{
	int i, j;

	if (row == 8) {
		_max = _max > val ? _max : val;
		return;
	}
	for (i = 0; i < 8; ++i)
		if (can_place(row, i)) {
			prev_pos[row] = i;
			val += G[row][i];
			dfs(row + 1);
			val -= G[row][i];
		}
}

int main()
{
	int k;
	int i, j;
	int x;

	scanf("%d", &k);
	while (k-- > 0) {
		val = _max = 0;
		for (i = 0; i < 8; ++i)
			for (j = 0; j < 8; ++j) {
				scanf("%d", &x);
				G[i][j] = x;
			}
		dfs(0);
		printf("%5d\n", _max);
	}
	return 0;
}
