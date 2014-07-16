#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

/*
 * 转化为01背包。关键是打印那里费了好多时间。
 */

#define N 21
#define MAX_PACK 10001

int C, n;
int a[N+1];
int f[N+1][MAX_PACK+1];

void print_ans(int i, int c) {
    if (i == 0)
        return;
    if (f[i][c] == f[i - 1][c])
        return print_ans(i - 1, c);

    for (int j = 1; j <= n; ++j)
        if (c >= a[j] && f[i][c] == f[i - 1][f[i][c] - a[j]] + a[i]) {
            print_ans(i - 1, f[i][c] - a[j]);
            cout << a[i] << " ";
            break;
        }
}

int main() {
    while (cin >> C >> n) {
        for (int i = 1; i <= n; ++i)
            cin >> a[i];

        memset(f, 0, sizeof(f));
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= C; ++j) {
                f[i][j] = f[i - 1][j];
                if (j - a[i] >= 0)
                    f[i][j] = max(f[i][j], f[i - 1][j - a[i]] + a[i]);
            }
        }
        print_ans(n, C);
        cout << "sum:" << f[n][C] << endl;
    }
    return 0;
}
