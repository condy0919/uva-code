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
#define eps (-2e-9)
#define inf 0x7f7f7f7f

using namespace std;

/*
 * 题目意思理解错了啊。。
 */

unsigned solve(unsigned n) {
    unsigned k = sqrt(n);
    unsigned ret = 0, cnt = 0;
    for (unsigned i = 2; i <= k && n > 1; ++i) {
        if (n % i == 0) {
            unsigned term = 1;
            while (n % i == 0) {
                term *= i;
                n /= i;
            }
            ret += term;
            ++cnt;
        }
    }
    if (n > 1 || cnt == 0) // prime | number like 3*7, or 1, 2
        ret += n, ++cnt;
    if (cnt == 1) // only one factor, FACTOR * 1 cases.
        ++ret;
    return ret;
}

int main() {
    ios::sync_with_stdio(false);

    unsigned int N;
    for (int cases = 0; cin >> N, N; ++cases) {
        cout << "Case " << 1 + cases << ": " << solve(N) << endl;
    }

    return 0;
}
