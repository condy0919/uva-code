#include <iostream>
#include <algorithm>
#include <cstring>

#define inf 0x7fffffff

/*
 * 就是dfs+记忆化啦！
 * 令我没有想到的是cin.ignore().ignore()这里竟然错了， 果然UVa上的数据格式不可靠啊。
 */

using namespace std;

struct chemicals {
    int type, heat;
} tbl[7][7];
int T;
int m;
int num[7], x;
int k;
int f[11][11][11][11][11][11];
char s[10];

int dp(int n1, int n2, int n3, int n4, int n5, int n6) {
    int& res = f[n1][n2][n3][n4][n5][n6];
    if (res != inf)
        return res;

    int a[] = {0, n1, n2, n3, n4, n5, n6};
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= m; ++j) {
            --a[i], --a[j];
            if (a[i] >= 0 && a[j] >= 0) {
                int product = tbl[i][j].type;
                ++a[product];
                res = min(res, dp(a[1], a[2], a[3], a[4], a[5], a[6]) + tbl[i][j].heat);
                --a[product];
            }
            ++a[i], ++a[j];
        }
    }
    if (res == inf)
        res = 0;
    return res; 
}

int main() {
    ios::sync_with_stdio(false);

    cin >> T;
    while (T-- > 0) {
        cin >> m;
        for (int i = 1; i <= m; ++i)
            for (int j = 1; j <= m; ++j)
                cin >> tbl[i][j].type >> tbl[i][j].heat;
        cin >> k;
        memset(num, 0, sizeof(num));
        for (int i = 1; i <= k; ++i) {
            cin >> x;
            ++num[x];
        }
        cin >> s;

        fill_n((int*)f, 11*11*11*11*11*11, inf);
        cout << dp(num[1], num[2], num[3], num[4], num[5], num[6]) << endl;
    }

    return 0;
}
