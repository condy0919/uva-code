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

/*
 * 枚举2个点，之后对存在的非前2个点进行枚举，统计出消了多少点。
 * dp(state) = min{dp(state ^ (1 << ...) + 1}
 * 由于直接枚举了2个点，因此要特殊化对1个点时的情况。
 */

#define rep(i, s, e) for (int i = s; i <= e; ++i)
#define pre(i, s, e) for (int i = s; i >= e; --i)

#define pi (acos(-1.0))
#define eps (1e-9)
#define inf 0x7f7f7f7f

using namespace std;

#define N ((1 << 16) + 1)

int x[17], y[17];
int n, m;
int f[N];

bool collinear(int i, int j, int k) {
    return (y[j] - y[i]) * (x[k] - x[j]) == (y[k] - y[j]) * (x[j] - x[i]);
}

int count(int x) {
    int ret = 0;
    while (x > 0) {
        ++ret;
        x &= (x - 1);
    }
    return ret;
}

int dp(int need, int state) {
    int& res = f[state];
    if (res != -1)
        return res;
    if (need <= 0)
        return res = 0;

    res = inf;
    for (int i = 0; i < n; ++i) {
        if (!(state & (1 << i)))
            continue;
        for (int j = i + 1; j < n; ++j) {
            if (!(state & (1 << j)))
                continue;
            int state_copy = state, cnt = 0;
            for (int k = 0; k < n; ++k) {
                if (k == i || k == j || !(state & (1 << k)))
                    continue;
                if (collinear(i, j, k)) {
                    state_copy ^= (1 << k);
                    ++cnt;
                }
            }
            state_copy ^= ((1 << i) | (1 << j));
            res = min(res, dp(need - cnt - 2, state_copy) + 1);
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    for (int cases = 1; cases <= T; ++cases) {
        cin >> n >> m;
        for (int i = 0; i < n; ++i)
            cin >> x[i] >> y[i];

        memset(f, -1, sizeof(f));
        for (int i = 0; i < n; ++i)
            f[1 << i] = 1;

        cout << "Case #" << cases << ":" << endl;
        cout << dp(m, (1 << n) - 1) << endl;
        if (cases != T)
            cout << endl;
    }

    return 0;
}
