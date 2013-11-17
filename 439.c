#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct xy_t {
	int x, y;
	int depth;
} xy_t;

static int dx[] = {-2, -2, -1, 1, 2, 2, 1, -1},
		   dy[] = {-1, 1, 2, 2, 1, -1, -2, -2};

char vis[8][8];
xy_t queue[64];
char src[3], dst[3];
xy_t st, ed;

char valid(int x, int y)
{
	if (x < 0 || x >= 8)
		return 0;
	if (y < 0 || y >= 8)
		return 0;
	return 1;
}

char cmp(xy_t* a, xy_t* b)
{
	return a->x == b->x && a->y == b->y;
}

int main()
{
	xy_t e, t;
	int cnt;
	int i, j;
	int dir;
	int _x, _y;

	while (scanf("%s%s", src, dst) == 2) {
		memset(vis, 0, sizeof(vis));
		cnt = 0;
		st.x = src[0] - 'a', st.y = src[1] - '1', st.depth = 0;
		ed.x = dst[0] - 'a', ed.y = dst[1] - '1';
		vis[st.x][st.y] = 1;
		queue[0] = st;
		for (i = 0, j = 1; i < j; ++i) {
			e = queue[i];
			if (cmp(&e, &ed))
				break;
			for (dir = 0; dir < 8; ++dir) {
				_x = e.x + dx[dir];
				_y = e.y + dy[dir];
				if (valid(_x, _y) && !vis[_x][_y]) {
					t.x = _x, t.y = _y, t.depth = e.depth + 1;
					vis[_x][_y] = 1;
					queue[j++] = t;
				}
			}
		}
		printf("To get from %s to %s takes %d knight moves.\n", src, dst, e.depth);
	}
	return 0;
}

