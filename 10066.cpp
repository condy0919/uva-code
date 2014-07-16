#include <iostream>
#include <algorithm>
#include <cstring>

/*
 * LCS
 *           { 1 + f(i - 1, j - 1), a[i] == b[j]
 * f(i, j) = { 0, i == 0 or j == 0
 *           { max{f(i, j - 1), f(i - 1, j)}, otherwise

 */

using namespace std;

#define N 101

int f[N][N];
int a[N], b[N];

int dp(int i, int j) {
    if (i == 0 || j == 0)
        return 0;
    if (f[i][j])
        return f[i][j];

    if (a[i] == b[j])
        return f[i][j] = 1 + dp(i - 1, j - 1);
    return f[i][j] = max(dp(i - 1, j), dp(i, j - 1));
}

int main() {
    int cases = 0;
    int la, lb;

    while (cin >> la >> lb, la || lb) {
        memset(f, 0, sizeof(f));
        for (int i = 1; i <= la; ++i)
            cin >> a[i];
        for (int i = 1; i <= lb; ++i)
            cin >> b[i];
        dp(la, lb);
        cout << "Twin Towers #" << ++cases << endl << "Number of Tiles : " << f[la][lb] << endl << endl;
    }
    return 0;
}
