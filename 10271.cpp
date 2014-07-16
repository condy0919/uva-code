#include <iostream>
#include <algorithm>

using namespace std;

#define inf 0x7f7f7f7f
#define diff(a,b) (((a)-(b))*((a)-(b)))

int T;
int K, N;
int L[5001];
int f[5001][1001];

/*
 * f[i][j] 代表前i个筷子中选出给了j个人的最小坏值.
 * f[i][j] = min{f[i-1][j], f[i-2][j-1] + diff}
 * 这里讲得好详细 -> http://blog.csdn.net/shuangde800/article/details/10952797
 */

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T-- > 0) {
        cin >> K >> N;
        K += 8;
        for (int i = 1; i <= N; ++i)
            cin >> L[i];
        reverse(L + 1, L + N + 1);
        for (int i = 0; i < 5001; ++i)
            fill(f[i] + 1, f[i] + 1001, inf);
        for (int i = 3; i <= N; ++i)
            for (int j = 1; j <= K; ++j) {
                f[i][j] = f[i - 1][j];
                if (i-2 - 3*(j - 1) >= 1 && f[i-2][j-1] != inf)
                    f[i][j] = min(f[i][j], f[i-2][j-1] + diff(L[i], L[i-1]));
            }
        cout << f[N][K] << endl;
    }
    return 0;
}
