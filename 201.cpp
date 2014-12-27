#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <bitset>
#include <utility>
#include <functional>
#include <numeric>
#include <limits>
#include <cmath>
#include <cctype>
#include <cstring>

#define rep(i, s, e) for (int i = s; i <= e; ++i)
#define pre(i, s, e) for (int i = s; i >= e; --i)

#define pi (acos(-1.0))
#define eps (1e-9)
#define inf 0x7f7f7f7f

using namespace std;

bool G[20][20];
int scnt[10];
int n;

bool is_square(int x, int y, int l) {
    // (x, y) -> (x, y + 2 * l)
    for (int i = y; i <= y + 2 * l; ++i)
        if (!G[x][i])
            return false;
    // (x, y) -> (x + 2 * l, y)
    for (int i = x; i <= x + 2 * l; ++i)
        if (!G[i][y])
            return false;
    // (x, y + 2 * l) -> (x + 2 * l, y + 2 * l)
    for (int i = x; i <= x + 2 * l; ++i)
        if (!G[i][y + 2 * l])
            return false;
    // (x + 2 * l, y) -> (x + 2 * l, y + 2 * l)
    for (int i = y; i <= y + 2 * l; ++i)
        if (!G[x + 2 * l][i])
            return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);

    int m;
    char dir;
    int x, y;
    int cases = 0;
    while (cin >> n >> m) {
        if (cases)
            cout << "\n**********************************\n\n";
        cout << "Problem #" << ++cases << "\n\n";
        memset(G, 0, sizeof(G));
        memset(scnt, 0, sizeof(scnt));
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                G[2 * i - 1][2 * j - 1] = 1;
        while (m-- > 0) {
            cin >> dir >> x >> y;
            x = 2 * x - 1;
            y = 2 * y - 1;
            if (dir == 'H')
                G[x][y] = G[x][y + 1] = G[x][y + 2] = 1;
            else
                G[y][x] = G[y + 1][x] = G[y + 2][x] = 1;
        }

        for (int len = 1; len < n; ++len) {
            for (int i = 1; i <= n - len; ++i)
                for (int j = 1; j <= n - len; ++j)
                    if (is_square(2 * i - 1, 2 * j - 1, len))
                        ++scnt[len];
        }
        if (std::accumulate(scnt, scnt + 10, 0) == 0)
            cout << "No completed squares can be found.\n";
        else
            for (int i = 1; i < n; ++i)
                if (scnt[i])
                    cout << scnt[i] << " square (s) of size " << i << '\n';
    }

    return 0;
}
