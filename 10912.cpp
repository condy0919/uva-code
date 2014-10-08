#include <iostream>

using namespace std;

/*
 * http://www.cnblogs.com/staginner/archive/2011/12/17/2291308.html
 * 状态又想错了。。看题解以为明白了意思，没有想到状态的改变又不对。。。
 * QAQ...
 */

int f[27][27][352];

int main() {
    ios::sync_with_stdio(false);

    f[0][0][0] = 1;
    for (int i = 1; i < 27; ++i) {
        for (int j = 0; j <= i; ++j) {
            for (int k = 0; k < 352; ++k) {
                f[i][j][k] = f[i - 1][j][k];
                if (j > 0 && k >= i)
                    f[i][j][k] += f[i - 1][j - 1][k - i];
            }
        }
    }

    int l, s;
    int cases = 0;
    while (cin >> l >> s, l || s) {
        cout << "Case " << ++cases << ": ";
        if (l > 26 || s > 26 * (26 + 1) / 2) {
            cout << "0" << endl;
            continue;
        }
        cout << f[26][l][s] << endl;
    }

    return 0;
}
