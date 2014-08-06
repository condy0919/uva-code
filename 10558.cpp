#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <bitset>
#include <utility>
#include <functional>
#include <numeric>
#include <limits>
#include <cmath>
#include <cctype>
#include <cstring>

/*
 * 坑：题目意思实现是太难懂。
 * http://www.cnblogs.com/staginner/archive/2011/12/05/2276832.html
 * http://www.cnblogs.com/scau20110726/archive/2012/10/04/2711436.html
 */

#define rep(i, s, e) for (int i = s; i <= e; ++i)
#define pre(i, s, e) for (int i = s; i >= e; --i)

#define pi (acos(-1.0))
#define eps (1e-9)
#define inf 0x7f7f7f7f

using namespace std;

int N, S, A, g[110][110], f[110][110], street[110];
int t[110][110], st[110][110][110], s[110][110], p[110][110];
int x, y;

void print_ans(int i, int k) {
    if (k != 1)
        print_ans(i - 1, p[i][k]);
    cout << " " << k;
}

int main() {
    ios::sync_with_stdio(false);

    while (cin >> N, N != -1) {
        memset(g, 0, sizeof(g));
        memset(t, 0, sizeof(t));
        for (int i = 0; i < N; ++i) {
            cin >> y >> x;
            g[x][y] = 1;
        }
        cin >> S;
        for (int i = 0; i < S; ++i)
            cin >> street[i];
        cin >> A;
        for (int i = 2; i <= 100; ++i) {
            for (int j = 1; j < S; ++j) {
                bool flag = false;
                for (int k = street[j - 1]; k < street[j]; ++k)
                    if (g[i - 1][k]) {
                        flag = true;
                        break;
                    }
                if (flag)
                    t[i][j] = 1;
            }
        }
        memset(s, 0, sizeof(s));
        memset(st, 0, sizeof(st));
        for (int i = 1; i < 100; ++i) {
            for (int j = i + 1; j <= 100; ++j) {
                for (int k = 1; k < S; ++k)
                    st[i][j][k] |= st[i][j - 1][k];
                for (int k = 1; k < S; ++k)
                    st[i][j][k] |= t[j][k];
                for (int k = 1; k < S; ++k)
                    if (st[i][j][k])
                        ++s[i][j];
            }
        }

        memset(f, -1, sizeof(f));
        for (int i = 2; i <= 100; ++i) {
            f[1][i] = s[1][i];
            p[1][i] = 1;
        }
        for (int i = 2; i < A; ++i) {
            for (int j = i + 1; j <= 100; ++j) {
                for (int k = i; k < j; ++k)
                    if (f[i - 1][k] + s[k][j] > f[i][j]) {
                        f[i][j] = f[i - 1][k] + s[k][j];
                        p[i][j] = k;
                    }
            }
        }
        cout << A;
        print_ans(A - 1, 100);
        cout << endl;
    }

    return 0;
}
