#include <iostream>
#include <algorithm>
#include <cstring>

/*
 * LCS的非递归版本。
 */

using namespace std;

#define N 101

int f[N][N];
int a[N], b[N];

int main() {
    int la, lb;
    int cases = 0;
    while (cin >> la >> lb, la || lb) {
        memset(f, 0, sizeof(f));
        for (int i = 0; i < la; ++i)
            cin >> a[i];
        for (int i = 0; i < lb; ++i)
            cin >> b[i];
        for (int i = 0; i < la; ++i)
            for (int j = 0; j < lb; ++j) {
                if (a[i] == b[j])
                    f[i + 1][j + 1] = f[i][j] + 1;
                else
                    f[i + 1][j + 1] = max(f[i][j + 1], f[i + 1][j]);
            }
        cout << "Twin Towers #" << ++cases << endl << "Number of Tiles : " << f[la][lb] << endl << endl;
    }
    return 0;
}
