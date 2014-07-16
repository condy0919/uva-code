#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

/*
 * f[i][j]代表在[i,j]这个范围内可以矩阵连乘达到的最少次数。
 * 则f[i][j] = min{f[i][k] + f[k+1][j] + 操作数ops[i][k], ops[k+1][j]}
 */

#define inf 0x7f7f7f7f

struct matrix {
    int x, y;
} M[11];
int n;

int f[11][11];
matrix ops[11][11];

int op(int a, int b, int c, int d) {
    int x1 = ops[a][b].x, y1 = ops[a][b].y;
    int x2 = ops[c][d].x, y2 = ops[c][d].y;
    return x1 * y1 * y2;
}

void print_ans(int l, int r) {
    if (l >= r) {
        if (l == r)
            cout << "A" << l;
        return;
    }
    cout << "(";
    for (int i = l; i < r; ++i)
        if (f[l][i] != inf && f[i + 1][r] != inf && f[l][r] == f[l][i] + f[i + 1][r] + op(l, i, i + 1, r)) {
            print_ans(l, i);
            cout << " x ";
            print_ans(i + 1, r);
            break;
        }
    cout << ")";
}

int main() {
    ios::sync_with_stdio(false);
    int cases = 0;
    while (cin >> n, n) {
        memset(ops, 0, sizeof(ops));
        for (int i = 1; i <= n; ++i) {
            cin >> M[i].x >> M[i].y;
            ops[i][i] = {M[i].x, M[i].y};
        }
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                f[i][j] = (i == j) ? 0 : inf;


        for (int len = 1; len <= n; ++len) {
            for (int i = 1; i + len <= n; ++i) {
                int j = i + len;
                for (int k = i; k < j; ++k)
                    if (f[i][k] != inf && f[k + 1][j] != inf && f[i][j] > f[i][k] + f[k + 1][j] + op(i, k, k + 1, j)) {
                        f[i][j] = f[i][k] + f[k + 1][j] + op(i, k, k + 1, j);
                        ops[i][j] = {ops[i][k].x, ops[k + 1][j].y};
                    }
            }
        }

        cout << "Case " << ++cases << ": ";
        print_ans(1, n);
        cout << endl;
    }
    return 0;
}
