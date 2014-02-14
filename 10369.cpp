#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;

struct edge_t {
	int u, v;
	double len;

	edge_t() {}
	edge_t(int _u, int _v, double _len) {
		u = _u;
		v = _v;
		len = _len;
	}

	bool operator<(const edge_t& rh) const {
		return len < rh.len;
	}
};

int S, P;
int x[600], y[600];
int f[600];

int find(int x)
{
	if (x != f[x])
		f[x] = find(f[x]);
	return f[x];
}

double kruskal()
{
	int i, j;
	vector<edge_t> E;
	int total_units;
	double ret = 0.0;

	for (i = 0; i < P; ++i)
		for (j = i + 1; j < P; ++j) {
			int a = x[i] - x[j], b = y[i] - y[j];
			double dis = hypot(a, b);
			E.push_back(edge_t(i, j, dis));
		}
	sort(E.begin(), E.end());

	for (i = 0, total_units = P; total_units > S; ++i) {
		int a = E[i].u, b = E[i].v;

		if (find(a) != find(b)) {
			f[find(a)] = find(b);
			--total_units;
			ret = E[i].len;
		}
	}
	return ret;
}

int main()
{
	int cases;

	cin >> cases;
	while (cases-- > 0) {
		cin >> S >> P;
		for (int i = 0; i < P; ++i) {
			cin >> x[i] >> y[i];
			f[i] = i;
		}
		printf("%.2lf\n", kruskal());
	}
	return 0;
}
