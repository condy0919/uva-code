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
 * 初始条件又弄错了..
 */

#define rep(i, s, e) for (int i = s; i <= e; ++i)
#define pre(i, s, e) for (int i = s; i >= e; --i)

#define pi (acos(-1.0))
#define eps (1e-9)
#define inf 0x7f7f7f7f

using namespace std;

long long f[14][14];
long long C[14][14];

long long factorial(long long n) {
    long long ret = 1;
    while (n > 0)
        ret *= n--;
    return ret;
}

int main() {
    ios::sync_with_stdio(false);

    C[0][0] = C[1][0] = C[1][1] = 1;
    for (int i = 2; i < 14; ++i) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j)
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }
    f[0][0] = 1;
    for (int i = 1; i < 14; ++i)
        for (int j = 1; j < 14; ++j)
            for (int k = j - 1; k <= i - 1; ++k)
                f[i][j] += C[i - 1][k] * factorial(i - 1 - k) * f[k][j - 1];

    int T;
    int N, L, R;
    cin >> T;
    while (T-- > 0) {
        cin >> N >> L >> R;
        if (L == 0 || R == 0 || L > N || R > N) {
            cout << "0" << endl;
            continue;
        }
        long long ans = 0;
        for (int i = L - 1; i <= N - R; ++i)
            ans += C[N - 1][i] * f[i][L - 1] * f[N - 1 - i][R - 1];
        cout << ans << endl;
    }

    return 0;
}
