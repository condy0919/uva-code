#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cctype>

/*
 * 空树的情况没有考虑到。。。
 */

using namespace std;

char matrix[201][201];
int rows, cols;

void get_matrix()
{
	char ch;
	rows = cols = 0;

	while (true) {
		ch = getchar();
		if (ch == '#')
			return;
		if (ch == '\n') {
			++rows;
			cols = 0;
			continue;
		}
		matrix[rows][cols++] = ch;
	}
}

int left(int row, int col)
{
	while (matrix[row][col] == '-')
		--col;
	return col + 1;
}

int right(int row, int col)
{
	while (matrix[row][col] == '-')
		++col;
	return col - 1;
}

bool check(char ch)
{
	if (!isprint(ch))
		return false;
	if (ch == '-' || ch == '|' || ch == '#' || ch == ' ')
		return false;
	return true;
}

bool solve(int row, int col_s, int col_e)
{
	int i;

	if (row >= rows)
		return false;

	putchar('(');
	for (i = col_s; i <= col_e; ++i)
		if (check(matrix[row][i])) {
			putchar(matrix[row][i]);
			if (matrix[row+1][i] != '|' || !solve(row + 3, left(row+2, i), right(row+2, i)))
				printf("()");
		}
	putchar(')');
	return true;
}

int main()
{
	int T;
	
	scanf("%d", &T);
	getchar();
	while (T-- > 0) {
		memset(matrix, 0, sizeof(matrix));
		get_matrix();
		getchar();
		if (rows == 0) {
			puts("()");
			continue;
		}
		solve(0, 0, strlen(matrix[0]) - 1);
		putchar('\n');
	}
	return 0;
}
