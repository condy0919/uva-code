#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <bitset>
#include <utility>
#include <functional>
#include <numeric>
#include <limits>
#include <cmath>
#include <cctype>
#include <cstring>

#define rep(i, s, e) for (int i = s; i <= e; ++i)
#define pre(i, s, e) for (int i = s; i >= e; --i)

#define pi (acos(-1.0))
#define eps (1e-9)
#define inf 0x7f7f7f7f

using namespace std;

/*
 * f[i, j] = 1. if s[i] == s[j], then f[i, j] = f[i + 1, j - 1]; dir[i, j] = ...
 *           2. another f[i, j] = f[i, k] + f[k + 1, j]; also dir[i, j] = ...
 * 此题f[i, j]表示在[i, j]这个范围内最少增加的括号对数。则显然这个越小越好。
 * 参考：http://blog.csdn.net/iaccepted/article/details/6819631
 */

int T;
string s;
int f[101][101], dir[101][101];

void print_ans(int l, int r) {
    if (l > r)
        return;
    if (l == r) {
        if (s[l] == '(' || s[l] == ')')
            cout << "()";
        else
            cout << "[]";
        return;
    }
    if (dir[l][r] == -1) {
        cout << s[l];
        print_ans(l + 1, r - 1);
        cout << s[r];
        return;
    }
    print_ans(l, dir[l][r]);
    print_ans(dir[l][r] + 1, r);
}

int main() {
    ios::sync_with_stdio(false);

    (cin >> T).ignore();
    while (T-- > 0) {
        cin.ignore();
        getline(cin, s);

        memset(f, 0, sizeof(f));
        memset(dir, 0, sizeof(dir));
        for (int i = 0; i < s.length(); ++i)
            f[i][i] = 1;

        for (int len = 1; len < s.length(); ++len) {
            for (int i = 0; i + len < s.length(); ++i) {
                int j = i + len;
                f[i][j] = inf;
                if (s[i] == '(' && s[j] == ')' || s[i] == '[' && s[j] == ']') {
                    f[i][j] = f[i + 1][j - 1];
                    dir[i][j] = -1;
                }
                for (int k = i; k <= j; ++k) {
                    if (f[i][j] > f[i][k] + f[k + 1][j])
                        f[i][j] = f[i][k] + f[k + 1][j], dir[i][j] = k;
                }
            }
        }
        print_ans(0, s.length() - 1);
        cout << endl;
        if (T)
            cout << endl;
    }

    return 0;
}
