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
 * 矩阵快速幂.
 */

#define rep(i, s, e) for (int i = s; i <= e; ++i)
#define pre(i, s, e) for (int i = s; i >= e; --i)

#define pi (acos(-1.0))
#define eps (1e-9)
#define inf 0x7f7f7f7f

using namespace std;

int p;

struct matrix {
    int64_t a[2][2];

    matrix& operator%=(int p) {
        a[0][0] %= p;
        a[0][1] %= p;
        a[1][0] %= p;
        a[1][1] %= p;
        return *this;
    }

    matrix operator*(const matrix& rhs) {
        matrix ret = *this;
        ret *= rhs;
        return std::move(ret);
    }

    matrix& operator*=(const matrix& rhs) {
        const matrix t = *this;
        const int64_t (&b)[2][2] = rhs.a;

        a[0][0] = (t.a[0][0] * b[0][0] % p + t.a[0][1] * b[1][0] % p) % p;
        a[0][1] = (t.a[0][0] * b[0][1] % p + t.a[0][1] * b[1][1] % p) % p;
        a[1][0] = (t.a[1][0] * b[0][0] % p + t.a[1][1] * b[1][0] % p) % p;
        a[1][1] = (t.a[1][0] * b[0][1] % p + t.a[1][1] * b[1][1] % p) % p;
        return *this;
    }
};

matrix powmod(matrix x, int n, int p) {
    matrix e = {1, 0, 0,1};

    while (n > 0) {
        if (n & 1) {
            e *= x;
            //e %= p;
        }
        x = x * x;
        //x %= p;
        n >>= 1;
    }
    return std::move(e);
}

int main() {
    ios::sync_with_stdio(false);

    matrix factor = {0, 1, 1, 1};
    int n, m;
    while (cin >> n >> m) {
        p = 1 << m;
        if (n == 0) {
            cout << "0" << endl;
            continue;
        }
        matrix ans = powmod(factor, n - 1, 1 << m);
        cout << ans.a[1][1] << endl;
    }

    return 0;
}
