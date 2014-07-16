#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdint>

using namespace std;

/*
 * 没有想到是用int64_t啊, 又可以用std::move来提速啊！C++11真是个好东西。
 * 总的思想就是f[x][y][s]表示 在(x, y)这个点上正好有s价值的状态的个数.
 * 而reachable[x][y][s]则表示 这个状态是否可达, vis_time[x][y][s]保证每个状态只计算一次。
 * 则f[x][y][s] = f[x+1][y左][s - 自身价值] + f[x+1][y右][s - 自身价值]
 * 关于y左、右，与x在上半层、下半层有关系。
 * 若x在上半层，则left(y)=y-1, right(y)=y
 * 若x在下半层，则left(y)=y, right(y)=y+1
 */

int N, S;
int vis_time[40][40][501];
int glasshouse[40][40];
bool reachable[40][40][501];
int64_t f[40][40][501];
string path[40][40];

int left(int x, int y) {
    if (x < N)
        return y - 1;
    return y;
}

int right(int x, int y) {
    if (x < N)
        return y;
    return y + 1;
}

int valid(int x, int y) {
    if (x < N)
        return y <= N + 1 - x && y >= 1;
    if (x <= 2 * N - 1)
        return y <= x - (N - 1) && y >= 1;
    return false;
}

bool dp(int x, int y, int s) {
    if (reachable[x][y][s])
        return true;
    if (++vis_time[x][y][s] >= 2)
        return false;
    int l = left(x, y), r = right(x, y);
    if (valid(x + 1, l) && s >= glasshouse[x][y] && dp(x + 1, l, s - glasshouse[x][y]) && reachable[x + 1][l][s - glasshouse[x][y]]) {
        f[x][y][s] += f[x + 1][l][s - glasshouse[x][y]];
        if (path[x][y].empty())
            path[x][y] = std::move("L" + path[x + 1][l]);
        else
            path[x][y] = std::move(min(path[x][y], std::move("L" + path[x + 1][l])));
        reachable[x][y][s] = true;
    }
    if (valid(x + 1, r) && s >= glasshouse[x][y] && dp(x + 1, r, s - glasshouse[x][y]) && reachable[x + 1][r][s - glasshouse[x][y]]) {
        f[x][y][s] += f[x + 1][r][s - glasshouse[x][y]];
        if (path[x][y].empty())
            path[x][y] = std::move("R" + path[x + 1][r]);
        else
            path[x][y] = std::move(min(path[x][y], std::move("R" + path[x + 1][r])));
        reachable[x][y][s] = true;
    }
    return reachable[x][y][s];
}

int main() {
    ios::sync_with_stdio(false);

    while (cin >> N >> S, N || S) {
        for (int i = 1, t = -N; i <= 2 * N - 1; ++i, ++t) {
            if (t == 0)
                t += 2;
            for (int j = 1; j <= abs(t); ++j)
                cin >> glasshouse[i][j];
        }
        // initialize
        memset(reachable, 0, sizeof(reachable));
        memset(vis_time, 0, sizeof(vis_time));
        memset(f, 0, sizeof(f));
        for (int i = 0; i < 40; ++i)
            for (int j = 0; j < 40; ++j)
                path[i][j].clear();
        for (int y = 1; y <= N; ++y) {
            f[2 * N - 1][y][glasshouse[2 * N - 1][y]] = 1;
            reachable[2 * N - 1][y][glasshouse[2 * N - 1][y]] = true;
        }

        for (int i = 1; i <= N; ++i)
            dp(1, i, S);
        
        int64_t ans = 0;
        int k = -1;
        for (int i = 1; i <= N; ++i)
            if (reachable[1][i][S]) {
                ans += f[1][i][S];
                if (k == -1)
                    k = i;
            }
        cout << ans << endl;
        if (ans != 0)
            cout << k - 1 << " " << path[1][k] << endl;
        else
            cout << endl;
    }

    return 0;
}
