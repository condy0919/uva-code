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
 * 思路来自这里:http://par.cse.nsysu.edu.tw/~advprog/advprog2008/11081.doc
 */

#define rep(i, s, e) for (int i = s; i <= e; ++i)
#define pre(i, s, e) for (int i = s; i >= e; --i)

#define pi (acos(-1.0))
#define eps (1e-9)
#define inf 0x7f7f7f7f
#define P 10007

using namespace std;

int T;
int f[61][61][61];
string a, b, res;

int dp(int i, int j, int k) {
    int& ans = f[i][j][k];
    if (ans != -1)
        return ans;

    ans = 0;
    for (int s = 1; s <= i; ++s)
        if (a[s - 1] == res[k - 1])
            ans = (ans + dp(s - 1, j, k - 1)) % P;
    for (int s = 1; s <= j; ++s)
        if (b[s - 1] == res[k - 1])
            ans = (ans + dp(i, s - 1, k - 1)) % P;
    return ans %= P;
}

int main() {
    ios::sync_with_stdio(false);

    cin >> T;
    while (T-- > 0) {
        cin >> a >> b >> res;
        memset(f, -1, sizeof(f));
        for (int i = 0; i < 61; ++i)
            for (int j = 0; j < 61; ++j)
                f[i][j][0] = 1;
        cout << dp(a.length(), b.length(), res.length()) << endl;
    }

    return 0;
}
