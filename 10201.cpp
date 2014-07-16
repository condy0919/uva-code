#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

/*
 * f[i][j] 表示在i点时j汽油这个状态时所花最小的金钱数。
 * 则f[i][j] 可由前一个点推出来。f[i][j] = f[i-1][j+dis];
 * 之后决定要加多少油才能使花费最小。
 * f[i][j] = min{f[i][k] + (j - k) * price[i]}, 其中k<=j.
 * http://www.cnblogs.com/staginner/archive/2011/11/30/2268942.html
 * ^ 参考。其中优化的地方的主要思想类似于最大连续和。
 * dp是弱项呀，一到复杂的状态就想不出来了，还是得多练、总结。
 */

#define inf 0x7f7f7f7f

int T, dis;
int d[101], price[101], n;
int f[101][201];
string line;

int dp() {
    for (int i = 0; i <= 100; ++i)
        fill(f[i], f[i] + 201, inf);
    f[0][100] = 0;
    
    for (int i = 1; i <= n; ++i) {
        int l = d[i] - d[i - 1];
        bool flag = false;
        for (int j = 0; j + l <= 200; ++j) {
            f[i][j] = f[i - 1][j + l];
            flag |= f[i][j] != inf;
        }
        if (!flag) // cannot reach.
            return -1;
        int min = inf;
        for (int j = 0; j <= 200; ++j) {
            min = std::min(min, f[i][j] - j * price[i]);
            f[i][j] = std::min(f[i][j], min + j * price[i]);
        }
    }
    if (dis - d[n] > 100 || f[n][100 + dis - d[n]] == inf)
        return -1;
    return f[n][100 + dis - d[n]];
}

int main() {
    ios::sync_with_stdio(false);

    cin >> T;
    while (T-- > 0) {
        (cin >> dis).ignore();
        n = 0;
        while (getline(cin, line), !line.empty()) {
            ++n;
            istringstream iss(line);
            iss >> d[n] >> price[n];
        }
        int ans = dp();
        if (ans < 0)
            cout << "Impossible" << endl;
        else
            cout << ans << endl;
        if (T)
            cout << endl;
    }
    return 0;
}
