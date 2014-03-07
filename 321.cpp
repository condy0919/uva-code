#include <algorithm>
#include <cstdio>
#include <cstring>

/*
 * 这个错的最不应该啊。没有想到是一开始的r/s/d的判断不对。
 * 害的我仿了别人的代码，结果还是不行。最后才发现是判断条件的问题。
 */

using namespace std;

struct state {
    int parent, id, lstate, step;
};

int r, d, s;
bool G[11][11];
int handle_light[11][11];
int len[11];

state Q[100003];
bool vis[100003];

bool try_to_insert(const state& s)
{
    int h = s.lstate * 10 + s.id - 1;
    if (vis[h])
        return false;
    return vis[h] = true;
}

int diff(int val)
{
	for (int i = 0; i < 15; ++i)
		if ((1 << i) == val)
			return i + 1;
	return 0;
}

void show_path(int cur)
{
	if (cur == 0)
		return;
    int parent = Q[cur].parent;
	show_path(parent);
    if (Q[parent].id != Q[cur].id)
        printf("- Move to room %d.\n", Q[cur].id);
    else if (Q[parent].lstate < Q[cur].lstate)
        printf("- Switch on light in room %d.\n", diff(Q[cur].lstate ^ Q[parent].lstate));
    else if (Q[parent].lstate > Q[cur].lstate)
        printf("- Switch off light in room %d.\n", diff(Q[cur].lstate ^ Q[parent].lstate));
}

void bfs()
{
    memset(vis, 0, sizeof(vis));

    int front = 0, rear = 1;
    Q[0].parent = 0, Q[0].id = 1;
    Q[0].lstate = 1, Q[0].step = 0;
    try_to_insert(Q[0]);
    while (front < rear) {
        state cur = Q[front];
        // 到达最终状态
        if (cur.id == r && (cur.lstate == (1 << (r - 1)))) {
            printf("The problem can be solved in %d steps:\n",
                   cur.step);
            show_path(front);
            return;
        }
        // 测试是否存在可前进路线且目的地须灯亮
        for (int i = 1; i <= r; ++i)
            if (G[cur.id][i] && (cur.lstate & (1 << (i - 1)))) {
                Q[rear].parent = front;
                Q[rear].id = i;
                Q[rear].lstate = cur.lstate;
                Q[rear].step = cur.step + 1;
                if (try_to_insert(Q[rear]))
                    ++rear;
            }
        // 测试可否在此地操作其他房间的灯
        for (int i = 0; i < len[cur.id]; ++i) {
            int op = handle_light[cur.id][i];
            Q[rear].parent = front;
            Q[rear].id = cur.id;
            Q[rear].lstate = (cur.lstate ^ (1 << (op - 1)));
            Q[rear].step = cur.step + 1;
            if (cur.id != op && try_to_insert(Q[rear]))
                ++rear;
        }
        ++front;
    }
    puts("The problem cannot be solved.");
}

int main()
{
    int cases = 0;
    while (scanf("%d%d%d", &r, &d, &s) , r + d + s) {// 错的就在这里。
        int x, y;
        memset(G, 0, sizeof(G));
        memset(len, 0, sizeof(len));
        for (int i = 0; i < d; ++i) {
            scanf("%d%d", &x, &y);
            G[x][y] = G[y][x] = true;
        }
        for (int i = 0; i < s; ++i) {
            scanf("%d%d", &x, &y);
            handle_light[x][len[x]++] = y;
        }
        printf("Villa #%d\n", ++cases);
        bfs();
        puts("");
    }
    return 0;
}
