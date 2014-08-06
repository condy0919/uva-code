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

#define MAXN ((1 << 16) + 1)

int N, M, f[MAXN], x[17], y[17], g[17][17];

using namespace std;

int count(int x) {
    int ret = 0;
    while (x > 0) {
        ++ret;
        x &= (x - 1);
    }
    return ret;
}

int dp(int state) {
    if (f[state] != -1)
        return f[state];
    if (N - count(state) >= M) // need <= cutted
        return f[state] = 0;

    int res = inf;
    for (int i = 0; i < N; ++i) {
        if (!((1 << i) & state))
            continue;
        for (int j = i + 1; j < N; ++j) {
            if ((1 << j) & state)
                res = min(res, dp(state & ~g[i][j]) + 1);
        }
    }
    return f[state] = res;
}

int main() {
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    for (int cases = 1; cases <= T; ++cases) {
        cin >> N >> M;
        for (int i = 0; i < N; ++i)
            cin >> x[i] >> y[i];
        memset(g, 0, sizeof(g));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i == j)
                    continue;
                for (int k = N - 1; k >= 0; --k) {
                    g[i][j] <<= 1;
                    if ((y[j] - y[i]) * (x[k] - x[i]) == (x[j] - x[i]) * (y[k] - y[i])) // i, j, k三点共线
                        g[i][j] |= 1;
                }
            }
        }
        memset(f, -1, sizeof(f));
        for (int i = 0; i < N; ++i)
            f[1 << i] = 1;
        cout << "Case #" << cases << ":" << endl;
        cout << dp((1 << N) - 1) << endl;
        if (cases != T)
            cout << endl;
    }

    return 0;
}
