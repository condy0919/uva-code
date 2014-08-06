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
 * 求出LCS，去除重叠部分的那个就是最小的啦！
 * 此外关于种数，那LCS有几种，它当然就有几种啦！
 */

#define rep(i, s, e) for (int i = s; i <= e; ++i)
#define pre(i, s, e) for (int i = s; i >= e; --i)

#define pi (acos(-1.0))
#define eps (1e-9)
#define inf 0x7f7f7f7f

using namespace std;

int T;
string a, b;
unsigned int f[31][31], cnt[31][31];

int main() {
    ios::sync_with_stdio(false);

    (cin >> T).ignore();
    for (int cases = 1; cases <= T; ++cases) {
        getline(cin, a);
        getline(cin, b);
        memset(f, 0, sizeof(f));
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < a.length() + 1; ++i)
            cnt[i][0] = 1;
        for (int i = 0; i < b.length() + 1; ++i)
            cnt[0][i] = 1;
        for (int i = 0; i < a.length(); ++i)
            for (int j = 0; j < b.length(); ++j) {
                if (a[i] == b[j]) {
                    f[i + 1][j + 1] = f[i][j] + 1;
                    cnt[i + 1][j + 1] = cnt[i][j];
                } else if (f[i][j + 1] > f[i + 1][j]) {
                    f[i + 1][j + 1] = f[i][j + 1];
                    cnt[i + 1][j + 1] = cnt[i][j + 1];
                } else if (f[i][j + 1] < f[i + 1][j]) {
                    f[i + 1][j + 1] = f[i + 1][j];
                    cnt[i + 1][j + 1] = cnt[i + 1][j];
                } else {
                    f[i + 1][j + 1] = f[i][j + 1];
                    cnt[i + 1][j + 1] = cnt[i + 1][j] + cnt[i][j + 1];
                }
            }
        cout << "Case #" << cases << ": ";
        cout << a.length() + b.length() - f[a.length()][b.length()] << " ";
        cout << cnt[a.length()][b.length()] << endl;
    }

    return 0;
}
