#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstring>
using namespace std;

/*
 * 一开始没有看清题意，导致样例看不懂。
 * 后来一查，才知道第1条信息是事件发生的时间而不是事件发生的顺序。
 * 搞清楚这个之后就是一个基本的LCS了。
 */

int correct[21], a[21], dp[21][21];
int n;

bool read() {
    int v;
    if (!(cin >> v))
        return false;
    a[v - 1] = 1;
    for (int i = 1; i < n; ++i) {
        cin >> v;
        a[v - 1] = i + 1;
    }
    return true;
}

int main() {
    int v;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> v;
        correct[v - 1] = i + 1;
    }
    while (read()) {
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                if (correct[i] == a[j])
                    dp[i + 1][j + 1] = dp[i][j] + 1;
                else
                    dp[i + 1][j + 1] = max(dp[i + 1][j], dp[i][j + 1]);
            }
        cout << dp[n][n] << endl;
    }
    return 0;
}
