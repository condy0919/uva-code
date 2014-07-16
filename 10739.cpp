#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <limits>
using namespace std;

/*
 * 基础dp。
 * 最小编辑距离的变形。
 */

#define N 1001

int f[N][N], T;
string s;

int dp(int i, int j) {
    if (i >= j)
        return 0;
    if (f[i][j])
        return f[i][j];

    if (s[i] == s[j])
        return f[i][j] = dp(i + 1, j - 1);
    return f[i][j] = min(dp(i, j - 1) + 1, min(dp(i + 1, j) + 1, dp(i + 1, j - 1) + 1));
}

int main() {
    cin >> T;
    for (int cases = 1; cases <= T; ++cases) {
        cout << "Case " << cases << ": ";
        cin >> s;

        memset(f, 0, sizeof(f));
        dp(0, s.length() - 1);
        cout << f[0][s.length() - 1] << endl;
    }
    return 0;
}
