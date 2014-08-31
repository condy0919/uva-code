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
#include <cstdint>

#define rep(i, s, e) for (int i = s; i <= e; ++i)
#define pre(i, s, e) for (int i = s; i >= e; --i)

#define pi (acos(-1.0))
#define eps (1e-9)
#define inf 0x7f7f7f7f

using namespace std;

/*
 * 经典的extgcd.
 */

int T;
int64_t x, k;
int64_t p, q;

void extgcd(int64_t a, int64_t b, int64_t& d, int64_t& x, int64_t& y) {
    if (b == 0) {
        d = a;
        x = 1;
        y = 0;
    } else {
        extgcd(b, a % b, d, y, x);
        y -= x * a/b;
    }
}

int main() {
    ios::sync_with_stdio(false);

    int64_t d;
    cin >> T;
    while (T-- > 0) {
        cin >> x >> k;
        extgcd(int64_t(ceil(1.0 * x / k)), x / k, d, q, p);
        cout << p * x / d << " " << q * x / d << endl;
    }


    return 0;
}
