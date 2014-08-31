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
 * 从n个数中找4个数的最小公倍数，然后对于指定长度的桌腿求比桌腿长度小但最接近的距离和比桌腿长度大但最接近的距离。
 * 又没有认真看题，又理解错题意了。。
 */

using namespace std;

int n, t;
unsigned coins[50], table;

unsigned gcd(unsigned a, unsigned b) {
    while (b) {
        unsigned r = a % b;
        a = b;
        b = r;
    }
    return a;
}

unsigned lcm(unsigned a, unsigned b) {
    return a / gcd(a, b) * b;
}

unsigned mint(unsigned a, unsigned b, unsigned c, unsigned d) {
    unsigned ret = lcm(a, b);
    ret = lcm(ret, c);
    return lcm(ret, d);
}

void solve() {
    unsigned fl_ans = 0, cl_ans = inf;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            for (int k = j + 1; k < n; ++k)
                for (int l = k + 1; l < n; ++l) {
                    unsigned multiples = mint(coins[i], coins[j], coins[k], coins[l]);
                    unsigned fl = (unsigned)floor(table * 1.0 / multiples) * multiples,
                             cl = (unsigned)ceil(table * 1.0 / multiples) * multiples;
                    if (fl <= table && fl >= fl_ans)
                        fl_ans = fl;
                    if (cl >= table && cl <= cl_ans)
                        cl_ans = cl;
                }
    cout << fl_ans << " " << cl_ans << endl;
}

int main() {
    ios::sync_with_stdio(false);

    while (cin >> n >> t, n || t) {
        for (int i = 0; i < n; ++i)
            cin >> coins[i];
        for (int i = 0; i < t; ++i) {
            cin >> table;
            solve();
        }
    }

    return 0;
}
