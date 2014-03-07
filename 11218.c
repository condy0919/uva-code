#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cases = 0;
int i, n;
int a, b, c, score;
struct {
	int a, b, c;
	int score;
} store[100];
char vis[10];
int ans;

int not_exist(int cur)
{
	int a, b, c;
	a = store[cur].a, b = store[cur].b, c = store[cur].c;
	return !vis[a] && !vis[b] && !vis[c];
}

void set(int cur)
{
	int a, b, c;
	a = store[cur].a, b = store[cur].b, c = store[cur].c;
	vis[a] = vis[b] = vis[c] = 1;
}

void unset(int cur)
{
	int a, b, c;
	a = store[cur].a, b = store[cur].b, c = store[cur].c;
	vis[a] = vis[b] = vis[c] = 0;
}

void dfs(int score, int item_num)
{
	int i;
	if (item_num == 3) {
		if (score > ans)
			ans = score;
		return;
	}
	for (i = 0; i < n; ++i) {
		if (not_exist(i)) {
			set(i);
			dfs(score + store[i].score, item_num + 1);
			unset(i);
		}
	}
}

int main()
{
	while (scanf("%d", &n), n) {
		memset(vis, 0, sizeof(vis));
		ans = -1;
		for (i = 0; i < n; ++i) {
			scanf("%d %d %d %d", &a, &b, &c, &score);
			store[i].a = a;
			store[i].b = b;
			store[i].c = c;
			store[i].score = score;
		}
		dfs(0, 0);
		printf("Case %d: %d\n", ++cases, ans);
	}
	return 0;
}
