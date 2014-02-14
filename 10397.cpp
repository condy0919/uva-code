#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cmath>

/*
 * 最小生成树的题。用了kruskal，初始的那几条连通边通过通过
 * 并查集将其放至同一棵树上。。。
 * 比较悲剧的是我想优化kruskal的运行时间，就将其在已经选了N-1-M条边之后
 * 退出循环，可爱的WA出现了。。。
 * 难道在初始的M条边中有重边？
 */

using namespace std;

struct xy_t {
	int x, y;
};

struct edge_t {
	double len;
	int p1, p2;

	edge_t(int _p1, int _p2, double _l) {
		p1 = _p1;
		p2 = _p2;
		len = _l;
	}

	bool operator<(const edge_t& rh) const {
		return len < rh.len;
	}
};

int N, M;
int f[750];
xy_t points[750];
vector<edge_t> E;

inline double dis(int a, int b)
{
	return sqrt(pow(points[a].x - points[b].x, 2) + pow(points[a].y - points[b].y, 2));
}

int find(int x)
{
	return x == f[x] ? x : (f[x] = find(f[x]));
}

double kruskal()
{
	double ret = 0.0;

	E.clear();
	for (int i = 0; i < N; ++i)
		for (int j = i + 1; j < N; ++j)
			E.push_back(edge_t(i, j, dis(i, j)));
	sort(E.begin(), E.end());

	for (int i = 0; i < E.size(); ++i) {
		int a = E[i].p1, b = E[i].p2;
		if (find(a) == find(b))
			continue;
		f[find(a)] = find(b);
		ret += E[i].len;
	}
	return ret;
}


int main()
{
	int node1, node2;

	while (cin >> N) {
		for (int i = 0; i < N; ++i) {
			cin >> points[i].x >> points[i].y;
			f[i] = i;
		}
		cin >> M;
		for (int i = 0; i < M; ++i) {
			cin >> node1 >> node2;
			f[find(node1 - 1)] = find(node2 - 1);
		}
		double ans = kruskal();
		printf("%.2lf\n", ans);
	}
	return 0;
}
