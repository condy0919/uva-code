#include <iostream>
#include <algorithm>
#include <string>
#include <cstdint>
#include <cstring>

using namespace std;

string s;
int N;
uint64_t dp[201];
const uint64_t limit = 0x7fffffff;

uint64_t f(int i) {
    if (dp[i])
        return dp[i];
    for (int k = 1; i + k <= s.length(); ++k) {
        uint64_t val = stoll(s.substr(i, k));
        if (val > limit)
            break;
        dp[i] = max(dp[i], f(i + k) + val);
        if (val == 0)
            break;
    }
    return dp[i];
}

int main() {
    cin >> N;
    while (N-- > 0) {
        cin >> s;
        memset(dp, 0, sizeof(dp));
        cout << f(0) << endl;
    }
    return 0;
}
