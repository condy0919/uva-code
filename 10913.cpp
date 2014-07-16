#include <iostream>
#include <cstring>
#include <stdint.h>

/*
 * 没有想到竟然会是溢出。..233
 * 一个基本的dp + 记忆化搜索。一开始是写3维的dp，发现各种难写，于是上网
 * 搜到改成4维的比较简洁。于是...
 * http://blog.csdn.net/shiqi_614/article/details/7028484
 * 万万没有想到是数据存不下了。
 */

using namespace std;

#define MAXN 80
#define inf ((int64_t)(1LL<<60))

// left, right, down
static const int dx[] = {0, 0, 1}, dy[] = {-1, 1, 0};
int N, K, G[MAXN][MAXN];
bool single[MAXN][MAXN];
int64_t f[MAXN][MAXN][7][3];
bool vis[MAXN][MAXN][7][3];

int64_t dp(int x, int y, int k, int dir) {
    bool& flag = vis[x][y][k][dir];
    int64_t& res = f[x][y][k][dir];

    if (flag)
        return res;

    if (x == N && y == N || k < 0) {
        flag = true;
        return res = (k < 0 ? -inf : G[N][N]);
    }

    res = -inf;
    int dec = (G[x][y] < 0 ? -1 : 0);
    for (int i = 0; i < 3; ++i) {
        int _x = x + dx[i], _y = y + dy[i];
        if (dir == 0 && i == 1 || dir == 1 && i == 0)
            continue;
        if (_x >= 1 && _x <= N && _y >= 1 && _y <= N && !single[_x][_y]) {
            single[_x][_y] = true;
            int64_t t = dp(_x, _y, k + dec, i);
            if (t != -inf)
                res = max(res, t + G[x][y]);
            single[_x][_y] = false;
        }
    }
    flag = true;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    int cases = 0;
    while (cin >> N >> K, N || K) {
        memset(vis, 0, sizeof(vis));
        memset(single, 0, sizeof(single));

        for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= N; ++j)
                cin >> G[i][j];
        if (G[N][N] < 0)
            --K;
        int64_t ans = dp(1, 1, K, 2);
        cout << "Case " << ++cases << ": ";
        if (ans != -inf)
            cout << ans << endl;
        else
            cout << "impossible" << endl;
    }
    return 0;
}
