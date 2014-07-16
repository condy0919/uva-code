#include <iostream>
#include <algorithm>

using namespace std;

/*
 * 果然这种是可能越界的。
 * f[city][day] 表示day天在city的最小花费。
 * 则f[city][day] = min{f[i][day-1] + cost[i][city][第day天]的花费} // 这里取模很有可能错.
 * 参考： http://www.cnblogs.com/kedebug/archive/2012/11/19/2776892.html
 */

#define inf 0x7fffffff

int n, k;
int day[11][11];
int cost[11][11][31];
int f[11][1001];

int main() {
    ios::sync_with_stdio(false);
    int cases = 0;
    while (cin >> n >> k, n || k) {
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                if (i != j) {
                    cin >> day[i][j];
                    for (int d = 1; d <= day[i][j]; ++d)
                        cin >> cost[i][j][d];
                }
        for (int i = 0; i < 11; ++i)
            fill(f[i], f[i] + 1001, inf);
        f[1][0] = 0;
        for (int d = 1; d <= k; ++d) {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    if (i == j)
                        continue;
                    int p = (d - 1) % day[j][i] + 1;
                    if (cost[j][i][p] != 0 && f[j][d - 1] != inf)
                        f[i][d] = min(f[i][d], f[j][d - 1] + cost[j][i][p]);
                }
            }
        }
        cout << "Scenario #" << ++cases << endl;
        if (f[n][k] != inf)
            cout << "The best flight costs " << f[n][k] << "." << endl << endl;
        else
            cout << "No flight possible." << endl << endl;
    }
    return 0;
}
