#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>

#define NOT_VISITED -1

using namespace std;

struct elem_t {
	int v;
	int color;

	elem_t(int _v=0, int _c=0):v(_v), color(_c) {}
};

int n, m;
bool G[200][200];
int state[200];

bool solve()
{
	elem_t e;
	queue<elem_t> Q;

	Q.push(elem_t(0, 0));
	state[0] = 0;
	while (!Q.empty()) {
		e = Q.front();
		Q.pop();
		for (int i = 0; i < n; ++i)
			if (G[e.v][i]) {
				G[e.v][i] = false;
				G[i][e.v] = false;

				if (state[i] != NOT_VISITED && state[i] == (e.color^1))
					continue;
				else if (state[i] != NOT_VISITED)
					return false;
				state[i] = e.color^1;
				Q.push(elem_t(i, e.color ^ 1));
			}
	}
	return true;
}

int main()
{
	while (cin >> n, n && cin >> m) {
		memset(G, false, sizeof(G));
		for (int i = 0; i < m; ++i) {
			int x, y;
			cin >> x >> y;
			G[x][y] = true;
			G[y][x] = true;
		}
		for (int i = 0; i < n; ++i)
			state[i] = NOT_VISITED;
		if (solve())
			cout << "BICOLORABLE.\n";
		else
			cout << "NOT BICOLORABLE.\n";
	}
	return 0;
}
