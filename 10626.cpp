#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

/*
 * 只考虑到了找零为1元的情况，没有想到找零时可能会有5元的出现。
 */

#define inf 0x7f7f7f7f

int f[701][151][51];

int dp(int n1, int n5, int n10, int n) {
    if (n == 0)
        return f[n1][n5][n10] = 0;
    if (f[n1][n5][n10] != -1)
        return f[n1][n5][n10];

    int min = inf;
    // 10  -> 8 + 1 + 1
    if (n10 >= 1)
        min = std::min(min, dp(n1 + 2, n5, n10 - 1, n - 1) + 1);
    // 5 + 5 -> 8 + 1 + 1
    if (n5 >= 2)
        min = std::min(min, dp(n1 + 2, n5 - 2, n10, n - 1) + 2);
    // 5 + 1 + 1 + 1 -> 8
    if (n5 >= 1 && n1 >= 3)
        min = std::min(min, dp(n1 - 3, n5 - 1, n10, n - 1) + 4);
    // 1 1 1 1 1 1 1 1 -> 8
    if (n1 >= 8)
        min = std::min(min, dp(n1 - 8, n5, n10, n - 1) + 8);
    // *important!!! 1 1 1 10 -> 8 + 5*
    if (n1 >= 3 && n10 >= 1)
        min = std::min(min, dp(n1 - 3, n5 + 1, n10 - 1, n - 1) + 4);
    return f[n1][n5][n10] = (min == inf ? -1 : min);
}

int main() {
    ios::sync_with_stdio(false);

    int cases;
    int n1, n5, n10;
    int need;

    cin >> cases;
    while (cases-- > 0) {
        cin >> need >> n1 >> n5 >> n10;
        memset(f, -1, sizeof(f));

        cout << dp(n1, n5, n10, need) << endl;
    }

    return 0;
}
