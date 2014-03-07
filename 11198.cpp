#include <iostream>
#include <algorithm>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include <cstring>

/*
 * c++11
 * 题目明明说了当第一个为0时结束，而我却判断第一个<=0时结束。
 * 唉，错就错在这此细小的地方啊。
 */

using namespace std;

static const bool is_primer[] = {0,0,1,1,0,1,0,1,0,0,0,1,0,1,0,0,0};
static const int fact[8] = {1,1,2,6,24,120,720,5040};

bool cmp(int a, int b) {
	return abs(a) < abs(b);
}

struct state {
	int a[8];
	int step;

	state() { step = 0; }
};

void left(state& s, int des, int item)
{
	int temp = s.a[item];
	if (item > des) {// des .... item
		for (int i = item; i > des; --i)
			s.a[i] = s.a[i - 1];
		s.a[des] = temp;
	} else {// item ... des
		for (int i = item; i < des - 1; ++i)
			s.a[i] = s.a[i + 1];
		s.a[des-1] = temp;
	}
}

void right(state& s, int des, int item)
{
	int temp = s.a[item];
	if (item > des) {// des ... item
		for (int i = item; i > des + 1; --i)
			s.a[i] = s.a[i - 1];
		s.a[des + 1] = temp;
	} else {// item ... des
		for (int i = item; i < des; ++i)
			s.a[i] = s.a[i + 1];
		s.a[des] = temp;
	}
}

bool vis[40320+1];
void mark(const state& s)
{
	int val = 0;
	for (int i = 0; i < 8; ++i) {
		int cnt = 0;
		for (int j = i + 1; j < 8; ++j)
			if (abs(s.a[i]) > abs(s.a[j]))
				++cnt;
		val += cnt * fact[8 - 1 - i];
	}
	vis[val] = true;
}

bool visited(const state& s)
{
	int val = 0;
	for (int i = 0; i < 8; ++i) {
		int cnt = 0;
		for (int j = i + 1; j < 8; ++j)
			if (abs(s.a[i]) > abs(s.a[j]))
				++cnt;
		val += cnt * fact[8 - 1 - i];
	}
	return vis[val];
}

int ans;
void bfs(state& beg)
{
	ans = -1;
	memset(vis, 0, sizeof(vis));

	queue<state> Q;
	Q.push(beg);
	mark(beg);
	while (!Q.empty()) {
		state e = Q.front(); Q.pop();
		if (is_sorted(e.a, e.a + 8, cmp)) {
			ans = e.step;
			return;
		}
		for (int i = 0; i < 8; ++i)
			for (int j = 0; j < 8; ++j) {
				if (i == j || e.a[i] * e.a[j] > 0)
					continue;
				int sum = abs(e.a[i]) + abs(e.a[j]);
				if (!is_primer[sum])
					continue;
				// a[j]移到a[i]的左边或右边
				// 左边
				state newone = e;
				left(newone, i, j);
				if (!visited(newone)) {
					++newone.step;
					Q.push(newone);
					mark(newone);
				}

				// 右边
				newone = e;
				right(newone, i, j);
				if (!visited(newone)) {
					++newone.step;
					Q.push(newone);
					mark(newone);
				}
			}
	}
}

int main()
{
	int t = 0;
	state beg;
	while (cin >> beg.a[0], beg.a[0]) {
		for (int i = 1; i < 8; ++i)
			cin >> beg.a[i];
		bfs(beg);
		printf("Case %d: %d\n", ++t, ans);
	}
	return 0;
}
