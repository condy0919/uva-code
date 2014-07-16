#include <iostream>
#include <algorithm>
#include <cstring>

/*
 * 明明是简单题，结果空串的情况没有考虑到，还有最大长度开太小了。
 */

using namespace std;

char s[1005];
int f[1005][1005];
int T;
int len;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    cin.ignore();
    while (T-- > 0) {
        cin.getline(s + 1, 1005);
        len = strlen(s + 1);

        memset(f, 0, sizeof(f));
        for (int i = 1; i <= len; ++i)
            f[i][i] = 1;

        for (int k = 1; k <= len; ++k) {
            for (int i = 1; i + k <= len; ++i) {
                int j = i + k;
                if (s[i] == s[j]) {
                    f[i][j] = f[i + 1][j - 1] + 2;
                } else {
                    f[i][j] = max(f[i + 1][j], f[i][j - 1]);
                }
            }
        }
        cout << f[1][len] << endl;
    }
    return 0;
}
