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
 * 条件概率，不知道怎么做。。都要哭了。。QAQ~
 * http://www.cnblogs.com/staginner/archive/2011/12/14/2287777.html
 */

using namespace std;
int c[5];
int n;
double r[13], p[13][5];

double dfs(int guest, double probability) {
    if (guest == n)
        return probability;

    double ret = 0;
    for (int i = 0; i < 5; ++i) {
        if (fabs(p[guest][i]) > eps && c[i] > 0) {
            --c[i];

            double t = dfs(guest + 1, probability * p[guest][i]);
            ret += t;

            if (guest == 0)
                r[i] += t; // 

            ++c[i];
        }
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);

    int t;

    cin >> t;
    while (t-- > 0) {
        cin >> n;
        cin >> c[0] >> c[1] >> c[2] >> c[3] >> c[4];
        for (int i = 0; i < n; ++i)
            cin >> p[i][0] >> p[i][1] >> p[i][2] >> p[i][3] >> p[i][4];

        memset(r, 0, sizeof(r));
        double P = dfs(0, 1);
        double item = 0, ans = -1;
        for (int i = 0; i < 5; ++i) {
            double t = r[i] / c[i];
            if (t > ans) {
                ans = t;
                item = i;
            }
        }
        cout << int(item + 1) << " " << setprecision(3) << setiosflags(ios::fixed) << ans / P << endl;
    }

    return 0;
}
