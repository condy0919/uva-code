#include <iostream>
#include <algorithm>
#include <numeric>

/*
 * 原来是自己在初始化f数组时长度没有指定好。233
 */

using namespace std;

int T, n;
int coins[105];
int f[50005];

int main() {
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        fill(f, f + 50005, 0);
        for (int i = 0; i < n; ++i)
            cin >> coins[i];
        int total = accumulate(coins, coins + n, 0);
        for (int i = 0; i < n; ++i)
            for (int j = total / 2; j - coins[i] >= 0; --j)
                f[j] = max(f[j], f[j - coins[i]] + coins[i]);
        cout << total - 2 * f[total / 2] << endl;
    }
    return 0;
}
