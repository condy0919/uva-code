#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>

/*
 * LCS，不过这个长度都没有说啊，还得自己尝试。
 */

using namespace std;

#define N 105

int dp[N][N];
string a, b;

int main() {
    int cases = 0;
    while (getline(cin, a), a[0] != '#' && getline(cin, b)) {
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < a.length(); ++i)
            for (int j = 0; j < b.length(); ++j) {
                if (a[i] == b[j])
                    dp[i + 1][j + 1] = dp[i][j] + 1;
                else
                    dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
            }
        cout << "Case #" + to_string(++cases) + ": you can visit at most " + to_string(dp[a.length()][b.length()]) + " cities." << endl;
    }

    return 0;
}
