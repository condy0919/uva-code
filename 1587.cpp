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

struct edge {
    int a, b;

    bool operator<(const edge& rhs) const {
        if (a != rhs.a)
            return a < rhs.a;
        return b < rhs.b;
    }
    bool operator==(const edge& rhs) const {
        return a == rhs.a && b == rhs.b;
    }
    bool operator!=(const edge& rhs) const {
        return !(*this == rhs);
    }
};

istream& operator>>(istream& is, edge& rhs) {
    is >> rhs.a >> rhs.b;
    if (rhs.a > rhs.b)
        swap(rhs.a, rhs.b);
    return is;
}

int main() {
    ios::sync_with_stdio(false);

    edge w[6];
    while (cin >> w[0]) {
        for (int i = 0; i < 5; ++i)
            cin >> w[i + 1];

        bool flag = true;
        sort(w, w + 6);
        for (int i = 0; i < 6; i += 2) {
            if (w[i] != w[i + 1]) {
                flag = false;
                break;
            }
        }
        if (w[0].a != w[2].a)
            flag = false;
        if (w[0].b != w[4].a)
            flag = false;
        if (w[2].b != w[4].b)
            flag = false;
        cout << (flag ? "POSSIBLE\n" : "IMPOSSIBLE\n");
    }

    return 0;
}
