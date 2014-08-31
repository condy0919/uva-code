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
 * 一开始没有想到要用欧拉函数啊，本来是两两判断是否互素的，结果肯定是超时的啊。
 * phi[n]表示在1~n中与n互素的数的个数。
 * 那么此题可以求出所有的phi..值，然后排除(1, 1)这个点对。
 */

#define N 50000

unsigned phi[N + 1], tbl[N + 1];

void phi_table() {
    phi[1] = 1;
    for (int i = 2; i <= N; ++i) {
        if (phi[i])
            continue;
        for (int j = i; j <= N; j += i) {
            if (!phi[j])
                phi[j] = j;
            phi[j] = phi[j] / i * (i - 1);
        }
    }
    partial_sum(phi, phi + N + 1, tbl);
}

int main() {
    ios::sync_with_stdio(false);

    phi_table();

    int n;
    while (cin >> n, n)
        cout << 2 * tbl[n] - 1 << endl;

    return 0;
}
