#include <iostream>
#include <iomanip>
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
 * 各种不会啊，压根就没有向dp方面想...
 * 参见: http://www.cnblogs.com/staginner/archive/2011/12/14/2287150.html
 */

using namespace std;

int n;
double p;

double f[501][501], e[501] = {1};

int main() {
    ios::sync_with_stdio(false);


    while (cin >> n >> p, n) {
        for (int i = 1; i <= n; ++i)
            e[i] = e[i - 1] * p;
        memset(f, 0, sizeof(f));
        fill(f[0], f[0] + n + 1, 1);
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= n; ++j) {
                f[i][j] = f[i - 1][j];
                if (i - 1 == j)
                    f[i][j] -= e[j + 1];
                else if (i - 1 > j)
                    f[i][j] -= f[i - 1 - j - 1][j] * (1 - p) * e[j + 1];
            }
        }
        double ans = 0;
        for (int i = 1; i <= n; ++i)
            ans += i * (f[n][i] - f[n][i - 1]);
        cout << setprecision(6) << setiosflags(ios::fixed) << ans << endl;
    }

    return 0;
}
