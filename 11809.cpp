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
#include <sstream>

#define rep(i, s, e) for (int i = s; i <= e; ++i)
#define pre(i, s, e) for (int i = s; i >= e; --i)

#define pi (acos(-1.0))
#define eps (1e-9)
#define inf 0x7f7f7f7f

/*
 * Stolen from http://blog.csdn.net/code4101/article/details/38303607
 */

using namespace std;

double C[10][31];

void init() {
    double f[10] = {0.5}, g[31];

    for (int i = 1; i < 10; ++i)
        f[i] = f[i - 1] / 2.0;
    partial_sum(f, f + 10, f); // UB??
    transform(f, f + 10, f, [](double x) { return log10(x); });
    for (int i = 1, v = 2; i < 31; ++i) {
        g[i] = (v - 1) * log10(2.0);
        v <<= 1;
    }
    for (int i = 0; i < 10; ++i)
        for (int j = 1; j < 31; ++j)
            C[i][j] = f[i] + g[j];
}

int main() {
    ios::sync_with_stdio(false);

    init();

    string s;
    while (cin >> s, s != "0e0") {
        double a = stod(s.substr(0, s.find_first_of('e'))),
               b = stod(s.substr(s.find_first_of('e') + 1));
        b = a = log10(a) + b;
        int x = 0, y = 1;
        for (int i = 0; i < 10; ++i) {
            for (int j = 1; j < 31; ++j) {
                if (fabs(a - C[i][j]) < b) {
                    x = i;
                    y = j;
                    b = fabs(a - C[i][j]);
                }
            }
        }
        cout << x << " " << y << endl;
    }

    return 0;
}
