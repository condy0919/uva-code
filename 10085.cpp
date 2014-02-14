#include <iostream>
#include <queue>
#include <algorithm>
#include <string>
#include <cstring>

/*
 * 基本的implicit graph traversal.
 */

using namespace std;

typedef int state[9];

const int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
const char* ref = "URDL";
bool vis[876543211];

struct state_t {
	string moves;
	state stat;

	state_t() {}
	state_t(state st, string moves = "") {
		memcpy(stat, st, sizeof(stat));
		this->moves = moves;
	}
	void show() {
		for (int i = 0; i < 9; ++i) {
			if ((i + 1) % 3 == 0)
				cout << stat[i] << endl;
			else
				cout << stat[i] << ' ';
		}
		cout << moves << endl;
	}
};

int convert(state st)
{
	int s = 0;
	for (int i = 0; i < 9; ++i)
		s = 10 * s + st[i];
	return s;
}

int zero_pos(state st)
{
	int i;
	for (i = 0; i < 9; ++i)
		if (st[i] == 0)
			break;
	return i;
}

void bfs(state_t start)
{
	state_t e;
	queue<state_t> Q;
	int _x, _y, _z, z;

	vis[convert(start.stat)] = true;
	Q.push(start);
	while (!Q.empty()) {
		e = Q.front(); Q.pop();

		for (int i = 0; i < 4; ++i) {
			z = zero_pos(e.stat);
			_x = z / 3 + dx[i];
			_y = z % 3 + dy[i];

			if (_x < 0 || _x > 2 || _y < 0 || _y > 2)
				continue;
			_z = 3 * _x + _y;
			swap(e.stat[_z], e.stat[z]);
			if (!vis[convert(e.stat)]) {
				vis[convert(e.stat)] = true;
				Q.push(state_t(e.stat, e.moves + ref[i]));
			}
			swap(e.stat[_z], e.stat[z]);
		}
	}
	e.show();
}

int main()
{
	int cases, round = 0;
	int v;
	state start;
	
	cin >> cases;
	while (round < cases) {
		cout << "Puzzle #" << ++round << endl;
		memset(vis, 0, sizeof(vis));
		for (int i = 0; i < 9; ++i)
			cin >> start[i];
		bfs(state_t(start));
		cout << endl;
	}
	return 0;
}
