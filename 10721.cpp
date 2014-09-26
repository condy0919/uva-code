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

/*
 * f[k][n]表示用k个bar来代表n有多少种组成方式。
 * 则f[k][n] = sum(f[k-1][t]), 其中t的变化范围在n - [1, min(m, n)]
 */

int main() {
    ios::sync_with_stdio(false);

    int n, k, m;
    long long int f[51][51];
    while (cin >> n >> k >> m) {
        memset(f, 0, sizeof(f));
        f[0][0] = 1;
        for (int i = 1; i <= k; ++i)
            for (int j = 1; j <= n; ++j)
                for (int k = 1; k <= j && k <= m; ++k)
                    f[i][j] += f[i - 1][j - k];
        cout << f[k][n] << endl;
    }

    return 0;
}
