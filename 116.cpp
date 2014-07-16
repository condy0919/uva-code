#include <iostream>
#include <algorithm>
#include <limits>
#include <cstring>
#include <stdint.h>

using namespace std;

/*
 * d(x, y) 表示从(x, y) 到 m-1列的最短路径。
 * d(x, y) = min{d(x-1,y+1), d(x,y+1), d(x+1,y+1)} + G[x][y]
 */

const int64_t inf = ((1UL<<31) * 10 + 1);
const int dx[] = {-1, 0, 1};

int n, m;
int64_t G[15][105];
int64_t d[15][105];
bool vis[15][105];
int next[15][105];

int64_t dfs(int x, int y) {
    if (vis[x][y] || y == m - 1)
        return d[x][y];

    vis[x][y] = true;
    int _x, _y = y + 1;
    int p[3];
    for (int i = 0; i < 3; ++i) {
        _x = x + dx[i];
        if (_x >= n)
            _x -= n;
        if (_x < 0)
            _x += n;
        p[i] = _x;
    }
    sort(p, p + 3); // 这里保证所求得的是字典序最小。
    for (int i = 0; i < 3; ++i) {
        _x = p[i];
        if (d[x][y] > dfs(_x, _y) + G[x][y]) {
            d[x][y] = d[_x][_y] + G[x][y];
            next[x][y] = _x;
        }
    }
    return d[x][y];
}

void print_ans(int x, int y) {
    while (y < m - 1) {
        cout << " " << next[x][y] + 1;
        x = next[x][y];
        ++y;
    }
}

int main() {
    while (cin >> n >> m) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                cin >> G[i][j];

        for (int i = 0; i < n; ++i)
            fill(d[i], d[i] + m, inf);
        for (int i = 0; i < n; ++i)
            d[i][m - 1] = G[i][m - 1];

        memset(vis, 0, sizeof(vis));

        int x = 0;
        int64_t ans = numeric_limits<int64_t>::max();
        for (int i = 0; i < n; ++i) {
            if (ans > dfs(i, 0)) {
                ans = d[i][0];
                x = i;
            }
        }
        cout << x + 1;
        print_ans(x, 0);
        cout << endl << ans << endl;
    }
    return 0;
}
