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
 * Catalan数。。。
 */

#define rep(i, s, e) for (int i = s; i <= e; ++i)
#define pre(i, s, e) for (int i = s; i >= e; --i)

#define pi (acos(-1.0))
#define eps (1e-9)
#define inf 0x7f7f7f7f

using namespace std;

unsigned long c[11] = {1, 1};

int main() {
    ios::sync_with_stdio(false);

    for (int i = 2; i < 11; ++i)
        c[i] = c[i - 1] * 2 * (2 * i - 1) / (i + 1);

    bool first = true;
    int n;
    while (cin >> n) {
        if (first)
            first = false;
        else
            cout << endl;
        cout << c[n] << endl;
    }


    return 0;
}
