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

int divisor[3001], rem[3001], cnt[3001];
int n;

int main() {
    ios::sync_with_stdio(false);

    int a, b;
    while (cin >> a >> b) {
        n = 0;
        memset(cnt, 0, sizeof(cnt));

        cout << a << "/" << b << " = " << a / b << ".";
        a %= b;
        while (!cnt[a] && a) {
            divisor[n] = a * 10 / b;
            rem[n] = a * 10 % b;
            cnt[a] = ++n;
            a = a * 10 % b;
        }
        if (a == 0) {
            for (int i = 0; i < n; ++i)
                cout << divisor[i];
            cout << "(0)\n";
            cout << "   1 = number of digits in repeating cycle\n\n";
            continue;
        }
        for (int i = 0; i + 1 < cnt[a]; ++i)
            cout << divisor[i];
        cout << "(";
        for (int i = cnt[a] - 1, k = 0; i < n && k < 50; ++i, ++k)
            cout << divisor[i];
        if (n - (cnt[a] - 1) > 50)
            cout << "...";
        cout << ")\n";
        cout << "   " << n - (cnt[a] - 1) << " = number of digits in repeating cycle\n\n";
    }

    return 0;
}
