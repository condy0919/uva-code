#include <iostream>
#include <algorithm>
#include <string>
#include <cstdint>

using namespace std;

int T;
string s;

/*
 * 看了题解还有的思路。
 * f(i, j) 表示在i到j这个区间内有多少个回文串。
 * 若s[i]==s[j], 则f(i, j) = f(i+1,j) + f(i,j-1) - f(i+1,j-1) + 1         +         1 * f(i+1,j-1);
 *                           ^ 右部分   ^ 左部分   ^ 中间重复   ^ s[i],s[j]自身     ^ 利用s[i], s[j] 与 中间部分合成回文串。
 * 若s[i]!=s[j], 则f(i, j) = f(i+1,j) + f(i,j-1) - f(i+1,j-1)
 *                           ^ 右部分   ^ 左部分   ^ 中间重复
 */

int64_t f[61][61];

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T-- > 0) {
        cin >> s;

        for (int i = 0; i < s.length(); ++i)
            f[i][i] = 1;
        for (int len = 1; len < s.length(); ++len) {
            for (int i = 0; i + len < s.length(); ++i) {
                int j = i + len;
                if (s[i] == s[j]) {
                    f[i][j] = f[i + 1][j] + f[i][j - 1] + 1;
                } else {
                    int64_t cost = i + 1 > j - 1 ? 0 : f[i + 1][j - 1];
                    f[i][j] = f[i + 1][j] + f[i][j - 1] - cost;
                }
            }
        }
        cout << f[0][s.length() - 1] << endl;
    }
    return 0;
}
