#include <iostream>
#include <algorithm>

/*
 * 看的这里。
 * http://www.cnblogs.com/staginner/archive/2011/12/22/2298304.html
 * 这里总结的特别好。
 * http://blog.csdn.net/hackerwin7/article/details/16972147
 */

using namespace std;

int a[3][3];
int w[] = {3,4,5,4,3};
int dist[6][5] = {
	{1,1,0,2,2},{1,2,0,1,2},{1,2,0,2,1},{2,1,0,1,2},{2,1,0,2,1},{2,2,0,1,1}
};
int _max;

void solve()
{
	for (int i = 0; i < 6; ++i)
		for (int j = 0; j < 6; ++j)
			for (int k = 0; k < 6; ++k) {
				if (i == j || i == k || j == k)
					continue;

				int s = 0;
				for (int t = 0; t < 5; ++t) {
					int da = dist[i][t], db = dist[j][t], dc = dist[k][t];
					s += w[t] * (a[0][da] + a[1][db] + a[2][dc]);
				}
				if (s > _max)
					_max = s;
			}
}

int main()
{
	int cases;
	
	cin >> cases;
	for (int round = 0; round < cases; ++round) {
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j)
				cin >> a[i][j];
			sort(a[i], a[i] + 3);
		}
		_max = 0;

		solve();
		cout << "Test #" << round + 1 << endl;
		cout << _max << endl << endl;
	}
}
