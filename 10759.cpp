#include <iostream>
#include <algorithm>
#include <numeric>

/*
 * 一开始在找规律，果断找不出来啊。。
 * 一搜没有想到是DP，瞬间就来灵感了...OAO.
 */

using namespace std;

typedef unsigned long long ULL;

ULL gcd(ULL a, ULL b) {
    while (b) {
        ULL r = a % b;
        a = b;
        b = r;
    }
    return a;
}

ULL pow(ULL x, ULL n) {
    ULL ret = 1;
    while (n > 0) {
        if (n & 1)
            ret *= x;
        n >>= 1;
        x *= x;
    }
    return ret;
}



int main() {
    ios::sync_with_stdio(false);

    ULL f[25][150] = { { 0 }, { 0, 1, 1, 1, 1, 1, 1 } };
    for (int i = 2; i <= 24; ++i)
        for (int j = i; j <= 6 * i; ++j)
            for (int k = 1; k <= std::min(6, j - 1); ++k)
                f[i][j] += f[i - 1][j - k];
    for (int i = 1; i <= 24; ++i)
        for (int j = 6 * i; j >= 0; --j)
            f[i][j] += f[i][j + 1];

    int n, x;
    while (cin >> n >> x, n || x) {
        if (f[n][x] == 0) {
            cout << "0" << endl;
        } else if (f[n][x] == pow(6, n)) {
            cout << "1" << endl;
        } else {
            ULL factor = gcd(f[n][x], pow(6, n));
            cout << f[n][x] / factor << "/" << pow(6, n) / factor << endl;
        }
    }

    return 0;
}
