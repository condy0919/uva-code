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
 * 分类讨论: 
 * l = (n + 1) / 2, 其为经过一次throwing之后剩下的牌数.
 *           当n为偶数时，经过一次throwing之后变成 2 4 6 .. 2l
 *           当n为奇数时，经过一次throwing之后变成 n 2 4 6 .. 2(l-1)
 */

#define rep(i, s, e) for (int i = s; i <= e; ++i)
#define pre(i, s, e) for (int i = s; i >= e; --i)

#define pi (acos(-1.0))
#define eps (1e-9)
#define inf 0x7f7f7f7f

using namespace std;

int f[500001] = {0, 1, 2};

int main() {
    ios::sync_with_stdio(false);

    for (int i = 3; i < 500001; ++i) {
        int remap = f[(i + 1) / 2];
        if (i % 2 == 1)
            f[i] = (remap == 1) ? i : (2 * (remap - 1));
        else
            f[i] = 2 * remap;
    }

    int n;
    while (cin >> n, n)
        cout << f[n] << endl;

    return 0;
}
