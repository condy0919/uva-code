#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

/*
 * 一个DAG上的dp。
 * 原来less是严格小于啊。less({1,2}, {1,2}) is true。所以将less改正确之后就对了。
 */

#define N 35

int a[N][15], d[N];
int _next[N];
bool G[N][N];
int k, n;

bool less_(int u, int v) {
    for (int i = 0; i < n; ++i)
        if (a[u][i] >= a[v][i])
            return false;
    return true;
}

int dp(int x) {
    if (d[x])
        return d[x];
    d[x] = 1;
    for (int i = 0; i < k; ++i)
        if (G[x][i]) {
            int val = dp(i) + 1;
            if (val > d[x]) {
                d[x] = val;
                _next[x] = i;
            }
        }
    return d[x];
}

int main() {
    while (cin >> k >> n) {
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < n; ++j)
                cin >> a[i][j];
            sort(a[i], a[i] + n);
        }
        memset(G, 0, sizeof(G));
        memset(d, 0, sizeof(d));
        fill(_next, _next + k, -1);
        for (int i = 0; i < k; ++i)
            for (int j = i + 1; j < k; ++j) {
                if (less_(i, j))
                    G[i][j] = true;
                else if (less_(j, i))
                    G[j][i] = true;
            }
        for (int i = 0; i < k; ++i)
            if (!d[i])
                dp(i);
        int* _max = max_element(d, d + k);
        cout << *_max << endl << _max - d + 1;
        for (int i = _next[_max - d]; i != -1; i = _next[i])
            cout << " " << i + 1;
        cout << endl;
    }
    return 0;
}
