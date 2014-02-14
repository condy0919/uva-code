#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <climits>
#include <cstring>

/*
 * prune这方面我确实是弱啊，都不会。。。
 * 参考http://blog.csdn.net/keshuai19940722/article/details/9772045
 */

using namespace std;

typedef pair<int, int> elem_t;
struct cmp {
	bool operator()(const elem_t& a, const elem_t& b) const {
		return a.second > b.second;
	}
};

int N, M;
bool G[36][36], vis[36];
int largest_adj_node[36];
int in_degree[36];
int _min;

void dfs(int node, int serv, int total)
{
	vector<int> used;
	bool flag = false;

	if (total == N) {
		_min = serv;
		return;
	} else if (node > N || serv >= _min)
		return;
	// if prev node hasn't been covered and there is no way to set it
	for (int i = 1; i < node; ++i)
		if (!vis[i] && largest_adj_node[i] < node)
			return;

	// set service station
	if (!vis[node]) {
		flag = true;
		vis[node] = true;
	}
	for (int i = 1; i <= N; ++i)
		if (G[node][i] && !vis[i]) {
			vis[i] = true;
			used.push_back(i);
		}
	// if adding the service station has no effect, do not 
	// waste a service station
	if (used.size() > 0 || flag)
		dfs(node + 1, serv + 1, total + used.size() + flag);
	for (int i = 0; i < used.size(); ++i)
		vis[used[i]] = false;
	if (flag)
		vis[node] = false;

	// not set
	dfs(node + 1, serv, total);
}

int greed()
{
	bool used[36] = {false};
	int ret = 0;
	int i, j;
	priority_queue<elem_t, vector<elem_t>, cmp> Q;

	for (i = 1; i <= N; ++i)
		Q.push(make_pair<int, int>(in_degree[i], i));

	while (!Q.empty()) {
		elem_t e = Q.top(); Q.pop();
		if (used[e.second])
			continue;
		used[e.second] = true;
		++ret;
		for (j = 1; j <= N; ++j)
			if (G[e.second][j])
				used[j] = true;
	}

	return ret;
}

int main()
{
	int x, y;

	while (cin >> N >> M, N || M) {
		memset(vis, 0, sizeof(vis));
		memset(G, 0, sizeof(G));
		memset(in_degree, 0, sizeof(in_degree));
		memset(largest_adj_node, 0, sizeof(largest_adj_node));
		for (int i = 0; i < M; ++i) {
			cin >> x >> y;
			G[x][y] = G[y][x] = true;
			largest_adj_node[x] = max(largest_adj_node[x], y);
			largest_adj_node[y] = max(largest_adj_node[y], x);
			++in_degree[x];
			++in_degree[y];
		}
		_min = greed();
		dfs(1, 0, 0);
		cout << _min << endl;
	}
	return 0;
}
