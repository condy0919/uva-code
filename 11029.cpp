#include <iomanip>
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

/*
 * 后3位通过快速幂模来做。
 * 前3位通过n^k / 10^([log10(n^k)] + 1 - 3) 化简来做。
 */

using namespace std;

typedef unsigned U;

U n, k;

U powmod(U n, U k, U m) {
    U ret = 1;
    while (k > 0) {
        if (k & 1)
            ret = ret * (n % m) % m;
        k >>= 1;
        n = (n % m) * (n % m) % m;
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while (T-- > 0) {
        cin >> n >> k;
        U TTT = powmod(n, k, 1000);
        U LLL = pow(10, 2 + fmod(k * log10(n), 1)/* - floor(k * log10(n))*/);
        cout << LLL << "..." << setw(3) << setfill('0') << TTT << endl;
    }

    return 0;
}
