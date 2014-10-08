#include <iostream>

#define rep(i, s, e) for (int i = s; i <= e; ++i)
#define pre(i, s, e) for (int i = s; i >= e; --i)

using namespace std;

/*
 * 设f[i][j][k]表示在前i个数中选了j个Mod D余k的个数。
 * 则在第i个时可选可不选。
 * 选择第i个时 f[i-1][j-1][t], 其中t要满足(t+a[i])%D == k, 可化简得到 t + a[i] = m * D + k; 
 * t = m * D + k - a[i] = ((k - a[i]) % D + D) % D
 * 不选择是 f[i-1][j][k]
 */

int a[201];
int f[201][201][21];

int main() {
    ios::sync_with_stdio(false);

    int N, Q;
    int D, M;
    int cases = 0;
    while (cin >> N >> Q, N || Q) {
        cout << "SET " << ++cases << ":" << endl;
        rep(i, 1, N)
            cin >> a[i];
        for (int q = 0; q < Q; ++q) {
            cout << "QUERY " << q + 1 << ": ";
            cin >> D >> M;
            
            f[0][0][0] = 1;
            rep(i, 1, N) {
                rep(j, 0, M) {
                    rep(k, 0, D - 1) {
                        f[i][j][k] = f[i - 1][j][k];
                        if (j > 0) {
                            int t = ((k - a[i]) % D + D) % D;
                            f[i][j][k] += f[i - 1][j - 1][t];
                        }
                    }
                }
            }
            cout << f[N][M][0] << endl;
        }
    }

    return 0;
}
