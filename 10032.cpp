#include <iostream>
#include <algorithm>
#include <numeric>
#include <cstring>

using namespace std;

int T;
int n;
int w[101];
int f[51][25000];

int main() {
    ios::sync_with_stdio(false);

    cin >> T;
    while (T-- > 0) {
        cin >> n;
        for (int i = 1; i <= n; ++i)
            cin >> w[i];
        int S = accumulate(&w[1], &w[n + 1], 0);
        int C = S / 2;

        int ans = -1;
        int up_bound = (n % 2) ? (n / 2 + 1) : (n  / 2);
        memset(f, 0, sizeof(f));
        f[0][0] = true;
        for (int i = 1; i <= n; ++i)
            for (int c = C; c >= w[i]; --c)
                for (int s = 1; s <= up_bound; ++s)
                    f[s][c] |= f[s - 1][c - w[i]];
        if (n % 2) {
            for (int i = C; i >= 0; --i)
                if (f[n / 2 + 1][i]) {
                    ans = max(ans, i);
                    break;
                }
        }
        for (int i = C; i >= 0; --i)
            if (f[n / 2][i]) {
                ans = max(ans, i);
                break;
            }
        cout << ans << " " << S - ans << endl;
        if (T)
            cout << endl;
    }
    return 0;
}
