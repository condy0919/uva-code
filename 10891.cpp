#include <iostream>
#include <algorithm>
#include <numeric>
#include <cstring>

using namespace std;

int a[100];
int n;
int d[100][100];
bool vis[100][100];

int dp(int i, int j) {
    if (vis[i][j])
        return d[i][j];
    vis[i][j] = true;
    int t = 0;
    for (int len = 0; len < j - i; ++len) {
        t = min(t, dp(i, i + len));
        t = min(t, dp(j - len, j));
    }
    return d[i][j] = accumulate(a + i, a + j + 1, 0) - t;
}

int main() {
    while (cin >> n, n) {
        for (int i = 0; i < n; ++i)
            cin >> a[i];
        memset(vis, 0, sizeof(vis));
        memset(d, 0, sizeof(d));
        int self = dp(0, n - 1);
        int other = accumulate(a, a + n, 0) - self;
        cout << self - other << endl;
    }
    return 0;
}
