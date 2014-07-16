#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

#define S(i,j) (s[j]-s[i-1])

int n, f[101][101], s[101];

int main() {
    while (cin >> n, n) {
        for (int i = 1; i <= n; ++i) {
            cin >> f[i][i];
            s[i] = s[i - 1] + f[i][i];
        }
        for (int len = 1; len < n; ++len) {
            for (int i = 1; i + len <= n; ++i) {
                int t = 0;
                for (int j = i; j < i + len; ++j)
                    t = min(t, f[j+1][i+len]);
                for (int j = i + len; j > i; --j)
                    t = min(t, f[i][j - 1]);
                f[i][i + len] = S(i, i + len) - t;
            }
        }
        cout << 2 * f[1][n] - S(1,n) << endl;
    }
    return 0;
}
