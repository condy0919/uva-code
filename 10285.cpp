#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>

/*
 * DAG上的最长距离。
 * d[x][y]代表在x/y这个坐标点为起点的最长距离。
 * d[x][y] = max{d[x][y]邻接的四个方向且在范围内且可以更新当前的数值}
 */

using namespace std;

int N;
string name;
int R, C;

int G[100][100];
int d[100][100];
bool vis[100][100];

int dp(int x, int y) {
    if (vis[x][y])
        return d[x][y];

    static int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
    int _x, _y;
    for (int i = 0; i < 4; ++i) {
        _x = x + dx[i];
        _y = y + dy[i];
        if (_x >= R || _x < 0 || _y >= C || _y < 0)
            continue;
        if (G[x][y] < G[_x][_y])
            d[x][y] = max(d[x][y], dp(_x, _y) + 1);
    }
    vis[x][y] = true;
    return d[x][y];
}

int main() {
    cin >> N;
    while (N-- > 0) {
        cin >> name >> R >> C;
        cout << name << ": ";
        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j)
                cin >> G[i][j];
        for (int i = 0; i < R; ++i)
            fill(d[i], d[i] + C, 1);
        memset(vis, 0, sizeof(vis));
        int _max = 1;
        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j)
                _max = max(_max, dp(i, j));
        cout << _max << endl;
    }
    return 0;
}
