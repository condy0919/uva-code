#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <cstdint>

/*
 * 主要一开始数组开小了，导致了WA，其他与uva674一样的思路。
 */

using namespace std;

#define eps 1e-6
#define N 6001

double coins;
uint64_t dp[N];
const int coin[11] = {1,2,4,10,20,40,100,200,400,1000,2000};

int main() {
    fill(dp, dp + N, 1);
    for (int i = 1; i < 11; ++i)
        for (int j = 0; j + coin[i] < N; ++j)
            dp[j + coin[i]] += dp[j];

    while (cin >> coins, fabs(coins) > eps)
        cout << setw(6) << setiosflags(ios::fixed) << setprecision(2) << coins << setw(17) << dp[int(coins*20)] << endl;
    return 0;
}
