#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

/*
 * f[i][j]代表在[i, j]这个范围内字符串可达到回文串的最少插入字符数。
 * 则f[i][j] = f[i+1][j-1] if s[i]==s[j] else min(f[i+1][j], f[i][j-1])+1
 * 关键是打印呀！
 */

enum pos_t {BOTH, LEFT, RIGHT};

int f[1005][1005];
pos_t parent[1005][1005];
char s[1005];

void ans(int l, int r) {
    if (l >= r) {
        if (l == r)
            cout << s[l];
        return;
    }

    pos_t p = parent[l][r];
    if (p == BOTH) {
        cout << s[l];
        ans(l + 1, r - 1);
        cout << s[r];
    } else if (p == LEFT) {
        cout << s[l];
        ans(l + 1, r);
        cout << s[l];
    } else {
        cout << s[r];
        ans(l, r - 1);
        cout << s[r];
    }
}

//string ans(int l, int r) {
//    if (l >= r)
//        return (l > r) ? string() : string(1, s[l]);
//
//    pos_t p = parent[l][r];
//    if (p == BOTH) {
//        return s[l] + ans(l + 1, r - 1) + s[r];
//    } else if (p == LEFT) {
//        return s[l] + ans(l + 1, r) + s[l];
//    } else {
//        return s[r] + ans(l, r - 1) + s[r];
//    }
//}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> (s + 1)) {
        int n = strlen(s + 1);
        memset(f, 0, sizeof(f));
        for (int len = 1; len <= n; ++len) {
            for (int i = 1; i + len <= n; ++i) {
                int j = i + len;
                if (s[i] == s[j]) {
                    f[i][j] = f[i + 1][j - 1];
                    parent[i][j] = BOTH;
                } else if (f[i + 1][j] < f[i][j - 1]) {
                    f[i][j] = f[i + 1][j] + 1;
                    parent[i][j] = LEFT;
                } else {
                    f[i][j] = f[i][j - 1] + 1;
                    parent[i][j] = RIGHT;
                }
            }
        }
        cout << f[1][n] << " ";
        ans(1, n);
        cout << endl;
        //cout << f[1][n] << " " << ans(1, n) << endl;
    }
    return 0;
}
