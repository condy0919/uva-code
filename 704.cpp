#include <iostream>
#include <cstring>
#include <cstdio>
#include <map>
#include <string>

#define MAXN 1000000

/*
 * 思路明白，还是没有写对啊。
 */

using namespace std;

map<string, int> vis;
map<string, int> back_vis;
typedef int state[24];
state goal = {0,3,4,3,0,5,6,5,0,1,2,1,0,7,8,7,0,9,10,9,0,1,2,1}, start;
state queue[MAXN];
int step[MAXN], parent[MAXN], path[MAXN], ans;
int back_parent[MAXN], back_path[MAXN];


// 旋转
void rotate(int* next, int* origin, int dir)
{
	memcpy(next, origin, sizeof(int) * 24);
	if (dir == 1) {// 左盘顺时针转
		memcpy(next + 2, origin, sizeof(int) * 10);
		next[0] = origin[10], next[1] = origin[11];
		next[21] = next[9], next[22] = next[10], next[23] = next[11];
	} else if (dir == 2) {// 右盘顺时针转
		memcpy(next + 9, origin + 11, sizeof(int) * 10);
		next[20] = origin[10], next[19] = origin[9];
		next[21] = next[9], next[22] = next[10], next[23] = next[11];
	} else if (dir == 3) {// 左盘逆时针转
		memcpy(next, origin + 2, sizeof(int) * 10);
		next[11] = origin[1], next[10] = origin[0];
		next[21] = next[9], next[22] = next[10], next[23] = next[11];
	} else if (dir == 4) {// 右盘逆时针转
		memcpy(next + 11, origin + 9, sizeof(int) * 10);
		next[9] = origin[19], next[10] = origin[20];
		next[21] = next[9], next[22] = next[10], next[23] = next[11];
	}
}

string change_state(state& s)
{
	string ret;
	for (int i = 0; i < 24; ++i)
		ret += s[i] + '0';
	return ret;
}

int try_to_insert(int s)
{
	string str = change_state(queue[s]);
	if (!vis[str]) {
		vis[str] = true;
		return true;
	}
	return false;
}

inline int back_try_to_insert(int s)
{
	string str = change_state(queue[s]);
	if (!back_vis[str]) {
		back_vis[str] = s;
		return true;
	}
	return false;
}

inline int opposite(int x)
{
	static int ref[] = {0, 3, 4, 1, 2};
	return ref[x];
}

// 逆向搜索
void back_bfs()
{
	memset(back_parent, 0, sizeof(back_parent));
	step[0] = step[1] = 0;
	back_vis.clear();
	back_vis[change_state(goal)] = 1;
	
	int front = 0, rear = 1;
	memcpy(queue[0], goal, sizeof(goal));

	while (front < rear) {
		state& cur = queue[front];
		if (step[front] > 8) {
			return;
		}
		for (int i = 1; i <= 4; ++i) {
			state& next = queue[rear];
			rotate(next, cur, i);
			step[rear] = step[front] + 1;
			if (back_try_to_insert(rear)) {
				back_parent[rear] = front;
				back_path[rear] = opposite(i);
				++rear;
			}
		}
		++front;
	}
}

// 正向搜索
void bfs()
{
	memset(parent, 0, sizeof(parent));

	step[0] = 0;
	vis.clear();
	vis[change_state(start)] = 1;
	
	memcpy(queue[0], start, sizeof(start));
	int front = 0, rear = 1;

	while (front < rear) {
		state& cur = queue[front];
		if (step[front] > 8) {
			++front;
			continue;
		}
		if (memcmp(cur, goal, sizeof(goal)) == 0) {
			ans = front;
			return;
		}
		if (back_vis[change_state(cur)]) {
			ans = front;
			return;
		}
		for (int i = 1; i <= 4; ++i) {
			state& next = queue[rear];
			rotate(next, cur, i);
			step[rear] = step[front] + 1;
			if (try_to_insert(rear)) {
				parent[rear] = front;
				path[rear] = i;
				++rear;
			}
		}
		++front;
	}
	ans = -1;
}

void print_path(int cur)
{
	if (cur) {
		print_path(parent[cur]);
		printf("%d", path[cur]);
	}
}

void print_back()
{
	string str = change_state(queue[ans]);
	int cur = back_vis[str];
	while (cur) {
		printf("%d", back_path[cur]);
		cur = back_parent[cur];
	}
}

int main()
{
	int T;

	back_bfs();

	scanf("%d", &T);
	while (T-- > 0) {
		for (int i = 0; i < 24; ++i)
			scanf("%d", &start[i]);

		if (memcmp(start, goal, sizeof(goal)) == 0) {
			puts("PUZZLE ALREADY SOLVED");
			continue;
		}
		bfs();
		if (ans != -1) {
			print_path(ans);
			print_back();
			puts("");
		} else {
			puts("NO SOLUTION WAS FOUND IN 16 STEPS");
		}
	}
	return 0;
}
