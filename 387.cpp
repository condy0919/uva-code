#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

/*
 * 题目意思又理解错了。。。
 */

using namespace std;

struct piece_t {
	int row, col;
	int area;
	bool shape[4][4];
} pieces[20];

int T;
int square[4][4];

void output_square()
{
	for (int i = 0; i < 4; ++i, puts(""))
		for (int j = 0; j < 4; ++j)
			printf("%d", square[i][j]);
}

bool can_place(const piece_t& piece, int x, int y)
{
	if (piece.col + y > 4 || piece.row + x > 4)
		return false;
	for (int i = 0; i < piece.row; ++i)
		for (int j = 0; j < piece.col; ++j)
			if (square[x + i][y + j] && piece.shape[i][j])
				return false;
	return true;
}

void cover(const piece_t& piece, int num, int x, int y)
{
	for (int i = 0; i < piece.row; ++i)
		for (int j = 0; j < piece.col; ++j)
			if (piece.shape[i][j])
				square[x + i][y + j] = num;
}

void uncover(const piece_t& piece, int num, int x, int y)
{
	for (int i = 0; i < piece.row; ++i)
		for (int j = 0; j < piece.col; ++j)
			if (piece.shape[i][j])
				square[x + i][y + j] = 0;
}

bool dfs(int choice, int blocks)
{
	if (blocks == 4 * 4)
		return choice == T;
	/*
	 * 一开始忘了这里，导致run time error.
	 */
	if (choice == T)
		return false;
	
	for (int x = 0; x < 4; ++x)
		for (int y = 0; y < 4; ++y)
			if (can_place(pieces[choice], x, y)) {
				cover(pieces[choice], choice + 1, x, y);
				if (dfs(choice + 1, blocks + pieces[choice].area))
					return true;
				uncover(pieces[choice], choice + 1, x, y);
			}
	return false;
}

int main()
{
	int first_line = 0;
	char s[20];
	while (cin >> T, T) {
		memset(pieces, 0, sizeof(pieces));
		memset(square, 0, sizeof(square));
		for (int i = 0; i < T; ++i) {
			cin >> pieces[i].row >> pieces[i].col;
			for (int j = 0; j < pieces[i].row; ++j) {
				cin >> s;
				for (int k = 0; k < pieces[i].col; ++k)
					pieces[i].area += (pieces[i].shape[j][k] = s[k] - '0');
			}
		}
		if (first_line++)
			puts("");
		if (dfs(0, 0))
			output_square();
		else
			puts("No solution possible");
	}
	return 0;
}
