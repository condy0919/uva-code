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

using std::cout;
using std::cin;

int left[100000 + 1], right[100000 + 1];

void link(int l, int r) {
    right[l] = r;
    left[r] = l;
}

void exchange(int x, int y) {
    int LX = left[x], LY = left[y];
    int RX = right[x], RY = right[y];
    if (right[x] == y) {
        link(LX, y);
        link(y, x);
        link(x, RY);
    } else if (right[y] == x) {
        link(LY, x);
        link(x, y);
        link(y, RX);
    } else {
        link(LX, y);
        link(y, RX);
        link(LY, x);
        link(x, RY);
    }
}

void print(int first, int n) {
    do {
        first = right[first];
        cout << first << " ";
    } while (--n > 0);
    cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    int cases = 0;
    while (cin >> n >> m) {
        cout << "Case " << ++cases << ": ";
        for (int i = 1; i <= n; ++i) {
            left[i] = i - 1;
            right[i] = (i + 1) % (n + 1);
        }
        right[0] = 1;
        left[0] = n;

        bool inv = false;
        int cmd, x, y;
        while (m-- > 0) {
            cin >> cmd;
            if (cmd == 4) {
                inv = !inv;
#ifndef ONLINE_JUDGE
                print(0, n);
#endif
                continue;
            }
            cin >> x >> y;
            if (cmd == 3) {
                exchange(x, y);
#ifndef ONLINE_JUDGE
                print(0, n);
#endif
                continue;
            } else if (inv) {
                cmd = 3 - cmd;
            }
            if (cmd == 1 && x == left[y] ||
                cmd == 2 && x == right[y])
                continue;

            int LX = left[x], RX = right[x];
            int LY = left[y], RY = right[y];
            if (cmd == 1) {
                link(LX, RX);
                link(LY, x);
                link(x, y);
            } else if (cmd == 2) {
                link(LX, RX);
                link(x, RY);
                link(y, x);
            }
#ifndef ONLINE_JUDGE
            print(0, n);
#endif
        }
        int b = 0;
        long long ans = 0;
        for (int i = 1; i <= n; ++i) {
            b = right[b];
            if (i & 1)
                ans += b;
        }
        if (inv && n % 2 == 0)
            ans = (long long)n * (n + 1) / 2 - ans;
        cout << ans << '\n';
    }

    return 0;
}
