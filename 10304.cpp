#include <iostream>
#include <numeric>
#include <algorithm>
#include <cstring>

using namespace std;

/*
 * 一开始没有看到是二分查找树,结果错了。
 * optimal(i, j) = min{optimal(i, k - 1) + optimal(k + 1, j) + Sum(i, j) - freq[k]}
 */

int n;
int f[251][251];
int S[251];
int freq[251];

#define sum(i, j) ((S[j]) - (S[i - 1]))
#define inf 0x7fffffff

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n) {
        for (int i = 1; i <= n; ++i)
            cin >> freq[i];
        partial_sum(freq + 1, freq + n + 1, S + 1);

        for (int len = 0; len < n; ++len) {
            for (int i = 1; i + len <= n; ++i) {
                int j = i + len;
                f[i][j] = inf;
                for (int k = i; k <= j; ++k)
                    f[i][j] = min(f[i][j], f[i][k - 1] + f[k + 1][j] + sum(i, j) - freq[k]);
            }
        }
        cout << f[1][n] << endl;
    }
    return 0;
}
