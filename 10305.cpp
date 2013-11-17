#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

bool R[101][101];
int in_degree[101];
bool vis[101];
int n, m;

int main()
{
	int a, b;
	while (cin >> n >> m, n || m) {
		memset(R, false, sizeof(R));
		memset(vis, false, sizeof(vis));
		for (int i = 0; i < m; ++i) {
			cin >> a >> b;
			R[a][b] = true;
		}
		for (int i = 1; i <= n; ++i) {
			int s = 0;
			for (int j = 1; j <= n; ++j)
				s += R[j][i];
			in_degree[i] = s;
		}

		for (int time = n; time > 0; --time) {
			int st;
			for (st = 1; st <= n; ++st)
				if (in_degree[st] == 0 && !vis[st])
					break;
			vis[st] = true;
			cout << st << " ";
			for (int i = 1; i <= n; ++i)
				if (R[st][i])
					--in_degree[i];
		}
		cout << endl;
	}
	return 0;
}
