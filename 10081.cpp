#include <iostream>
#include <iomanip>
#include <numeric>
#include <cstring>
#include <cmath>

#define rep(i, s, e) for (int i = s; i <= e; ++i)
#define pre(i, s, e) for (int i = s; i >= e; --i)

/*
 * 设f[i, j]表示在第i位是为j的个数.
 * 则f[i, j]可以由f[i-1,j-1], f[i-1,j], f[i-1,j+1]推来。
 * 结果则为f[n, 0 ~ k]的累和/总可能数..
 */

using namespace std;

double f[101][10];
int n, k;

int main() {
    ios::sync_with_stdio(false);

    while (cin >> k >> n) {
        if (n == 1) {
            cout << "100.00000\n";
            continue;
        }
        memset(f, 0, sizeof(f));
        fill_n(f[1], k + 1, 1.0);
        rep(i, 2, n) {
            f[i][0] = f[i - 1][0] + f[i - 1][1];
            rep(j, 1, k - 1) {
                f[i][j] = f[i - 1][j - 1] + f[i - 1][j] + f[i - 1][j + 1];
            }
            f[i][k] = f[i - 1][k - 1] + f[i - 1][k];
        }
        double ans = accumulate(f[n], f[n] + k + 1, 0.0);
        cout << setiosflags(ios::fixed) << setprecision(5) << 100.0 * ans / pow(k + 1, n)
             << endl;
    }

    return 0;
}
