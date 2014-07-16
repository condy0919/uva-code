#include <iostream>
#include <algorithm>
#include <bitset>

using namespace std;

/*
 * 多阶段的dp，主要是将状态压缩以保存结果信息。
 */

int T;
char s[13];
int f[4096];
bool vis[4096];

int dp(int state) {
    if (vis[state])
        return f[state];

    bool flag = false;
    for (int i = 0; i < 12; ++i) {
        if (i + 2 < 12 && (state & (1 << i)) && (state & (1 << (i + 1))) && (state & (1 << (i + 2))) == 0) {
            flag = true;
            f[state] = min(f[state], dp(state ^ (1 << i) ^ (1 << (i + 1)) ^ (1 << (i + 2))));
        }
        if (i - 1 >= 0 && (state & (1 << i)) && (state & (1 << (i + 1))) && (state & (1 << (i - 1))) == 0) {
            flag = true;
            f[state] = min(f[state], dp(state ^ (1 << i) ^ (1 << (i + 1)) ^ (1 << (i - 1))));
        }
    }
    vis[state] = true;
    if (!flag)
        return f[state] = bitset<12>(state).count();
    return f[state];
}

int main() {
    cin >> T;
    while (T--) {
        cin >> s;
        int state = 0;
        for (int i = 0; i < 12; ++i)
            if (s[i] == 'o')
                state |= (1 << i);
        fill(vis, vis + 4096, false);
        fill(f, f + 4096, 0xfff);
        cout << dp(state) << endl;
    }
    return 0;
}
