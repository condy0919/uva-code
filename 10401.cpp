#include <iostream>
#include <algorithm>
#include <string>
#include <numeric>
#include <cctype>
#include <cstring>
#include <stdint.h>

using namespace std;

/*
 * 这题题意理解错了，原以为？的作用是可有可无，原来是必须要有一个呀！
 */

int64_t f[16][16];
int n;

int hex2int(char ch) {
    if (isdigit(ch))
        return ch - '0';
    return ch - 'A' + 10;
}

int main() {
    ios::sync_with_stdio(false);

    string line;
    while (cin >> line) {
        memset(f, 0, sizeof(f));
        n = line.length();

        if (line[0] == '?') {
            fill_n(f[0], n, 1);
        } else {
            f[0][hex2int(line[0]) - 1] = 1;
        }

        for (int i = 1; i < n; ++i) {
            if (line[i] == '?') {
                for (int row = 0; row < n; ++row) {
                    for (int j = 0; j < row - 1; ++j)
                        f[i][row] += f[i - 1][j];
                    for (int j = row + 2; j < n; ++j)
                        f[i][row] += f[i - 1][j];
                }
            } else {
                int row = hex2int(line[i]) - 1;
                for (int j = 0; j < row - 1; ++j)
                    f[i][row] += f[i - 1][j];
                for (int j = row + 2; j < n; ++j)
                    f[i][row] += f[i - 1][j];
            }
        }
        cout << accumulate(f[n - 1], f[n - 1] + n, int64_t(0)) << endl;
    }

    return 0;
}
