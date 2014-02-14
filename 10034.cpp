#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <utility>
#include <cmath>
#include <cfloat>
#include <cstdio>

using namespace std;

#define INF DBL_MAX;
#define NOT_USED false
#define USED true

struct xy_t {
	double x, y;
};

struct elem_t {
	int idx;
	double dis;

	elem_t(int _idx, double _d):idx(_idx), dis(_d) {}
};

struct cmp {
	bool operator() (const elem_t& a, const elem_t& b) {
		return a.dis > b.dis;
	}
};

int n;
xy_t p[100];
double dis[100];

double d(int a, int b)
{
	return sqrt(pow(p[a].x - p[b].x, 2) + pow(p[a].y - p[b].y, 2));
}

double prim()
{
	double ret = 0.0;
	int i, j;
	bool vis[100] = {NOT_USED};

	priority_queue<elem_t, vector<elem_t>, cmp> Q;
	Q.push(elem_t(0, 0.0));
	while (!Q.empty()) {
		elem_t e = Q.top(); Q.pop();
		if (vis[e.idx] == USED)
			continue;

		vis[e.idx] = USED;
		ret += e.dis;

		// relax
		for (int i = 0; i < n; ++i)
			if (vis[i] == NOT_USED && d(e.idx, i) < dis[i]) {
				dis[i] = d(e.idx, i);
				Q.push(elem_t(i, dis[i]));
			}
	}

	return ret;
}

/*
 * the O(N^2) solution
 */
double prim_()
{
	double ret = 0.0;
	int i, j;
	bool vis[100] = {NOT_USED};

	for (i = 0; i < n; ++i) {
		// find the nearest vertex NON_USED;
		int idx = 0;
		double _min = INF;
		for (j = 0; j < n; ++j)
			if (vis[j] == NOT_USED && _min > dis[j]) {
				_min = dis[j];
				idx = j;
			}
		vis[idx] = USED;
		ret += _min;

		// relax other vertex NOT_USED
		for (j = 0; j < n; ++j)
			if (vis[j] == NOT_USED && d(idx, j) < dis[j])
				dis[j] = d(idx, j);
	}
}

int main()
{
	int test_case;

	cin >> test_case;
	while (test_case-- > 0) {
		cin >> n;
		for (int i = 0; i < n; ++i)
			cin >> p[i].x >> p[i].y;

		for (int i = 1; i < n; ++i)
			dis[i] = INF;
		dis[0] = 0.0;

		double ans = prim();
		printf("%.2lf\n", ans);
		if (test_case)
			putchar('\n');
	}

	return 0;
}
