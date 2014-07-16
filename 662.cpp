#include <iostream>
#include <algorithm>
#include <numeric>
#include <utility>
#include <cstring>

/*
 * f[i][j]代表前i个餐馆放置j个仓库所需的最小花费。
 * 则f[i][j] = min{f[k][j-1] + cost[k+1][i]}, for k in [j-1, i).
 * cost[a][b]代表[a, b]这个区域内放置1个仓库所花费 <- 这里可贪心。
 * 思路可简单，无奈想的时候总是以为O(N^2)的dp已经很慢了，不敢想下去。..233
 */

using namespace std;

#define inf 0x7f7f7f7f

int n, m;
int d[201];
int f[201][51];
int dis[201][201];
int info[201][201];

void prepare() {
    memset(dis, 0, sizeof(dis));

    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            dis[i][j] = dis[i][j - 1] + d[j] - d[(i + j) / 2];

    for (int i = 0; i < n; ++i)
        fill(f[i], f[i] + 201, inf);
    for (int i = 1; i <= n; ++i) {
        f[i][1] = dis[1][i];
        info[i][1] = 1;
    }
}

void print_ans(int n, int m) {
    if (m == 0)
        return;

    // serves [k, n]
    int k = info[n][m];

    print_ans(k - 1, m - 1);
    cout << "Depot " << m << " at restaurant " << (k + n) / 2 << " serves restaurant";
    if (k == n)
        cout << " " << k << endl;
    else
        cout << "s " << k << " to " << n << endl;
}

int main() {
    ios::sync_with_stdio(false);

    int chain = 0;
    while (cin >> n >> m, n || m) {
        for (int i = 1; i <= n; ++i)
            cin >> d[i];

        prepare();
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                for (int k = j - 1; k < i; ++k)
                    if (f[i][j] > f[k][j - 1] + dis[k + 1][i]) {
                        f[i][j] = f[k][j - 1] + dis[k + 1][i];
                        info[i][j] = k + 1;
                    }
        cout << "Chain " << ++chain << endl;
        print_ans(n, m);
        cout << "Total distance sum = " << f[n][m] << endl;
        cout << endl;
    }

    return 0;
}
