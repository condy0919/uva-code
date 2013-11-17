#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;

char maze[30][80+1];

bool not_vaild(int x, int y)
{
	char ch = maze[x][y];

	if (isprint(ch) && ch != '*' && ch != '_' && ch != ' ')
		return true;
	return false;
}

void dfs(int x, int y)
{
	static int dx[] = {-1, 0, 1, 0},
			   dy[] = {0, 1, 0, -1};
	int _x, _y;

	maze[x][y] = '#';
	for (int dir = 0; dir < 4; ++dir) {
		_x = x + dx[dir];
		_y = y + dy[dir];
		if (not_vaild(_x, _y) || maze[_x][_y] == '*')
			continue;
		dfs(_x, _y);
	}
}

int main()
{
	int n, i, j, k;

	cin >> n;
	cin.ignore();
	while (n-- > 0) {
		i = 0;
		while (true) {
			cin.getline(maze[i], sizeof(maze[i]));
			if (maze[i][0] == '_')
				break;
			++i;
		}
		bool found = false;
		for (j = 0; j < i && !found; ++j)
			for (k = 0; k < strlen(maze[j]); ++k)
				if (maze[j][k] == '*') {
					found = true;
					break;
				}
		if (found)
			dfs(j-1, k);
		for (j = 0; j < i+1; ++j)
			cout << maze[j] << endl;
	}
	return 0;
}
