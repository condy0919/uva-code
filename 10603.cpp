#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>

/*
 * basic implicit graph traversal.
 */

using namespace std;

inline int convert(int a, int b, int c)
{
	return a * 201 * 201 + b * 201 + c;
}

inline int convert(int v[])
{
	return convert(v[0], v[1], v[2]);
}

struct state_t {
	int state, amount;

	state_t() { state = amount = 0; }
	state_t(int a, int b, int c) {
		amount = 0;
		state = convert(a, b, c);
	}
	state_t(int cur[], int amount) {
		state = convert(cur);
		this->amount = amount;
	}
};

bool vis[201 * 201 * 201];
int lim[3], d;

void bfs()
{
	int cur[3], amount;
	int _d = 0, _amount;
	state_t e;
	queue<state_t> Q;

	Q.push(state_t(0, 0, lim[2]));
	vis[Q.front().state] = true;
	while (!Q.empty()) {
		e = Q.front(); Q.pop();
		int v[3] = {
			e.state / 201 / 201, e.state / 201 % 201, e.state % 201
		};

		for (int i = 0; i < 3; ++i)
			if (v[i] == d) {
				cout << e.amount << ' ' << d << endl;
				return;
			} else if (v[i] < d && v[i] > _d) {
				_d = v[i];
				_amount = e.amount;
			}

		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j) {
				if (i == j)
					continue;
				if (v[i] <= 0 || v[j] >= lim[j])
					continue;

				// second one full
				if (v[i] >= lim[j] - v[j]) {
					amount = lim[j] - v[j];
					cur[i] = v[i] - amount;
					cur[j] = lim[j];
					cur[3-i-j] = v[3-i-j];
				} else {// first empty
					amount = v[i];
					cur[i] = 0;
					cur[j] = v[j] + amount;
					cur[3-i-j] = v[3-i-j];
				}
				if (!vis[convert(cur)]) {
					vis[convert(cur)] = true;
					Q.push(state_t(cur, e.amount + amount));
				}
			}
	}
	cout << _amount << ' ' << _d << endl;
}

int main()
{
	int cases;

	cin >> cases;
	while (cases-- > 0) {
		cin >> lim[0] >> lim[1] >> lim[2] >> d;
		memset(vis, 0, sizeof(vis));
		bfs();
	}
	return 0;
}
