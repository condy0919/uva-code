#include <iostream>
#include <algorithm>
#include <numeric>
#include <cstring>

/*
 * 不懂，抄自
 * http://www.cnblogs.com/staginner/archive/2011/12/18/2292064.html
 */


using namespace std;

int f[1100000];
int a[5], b[5];

int dp(int state) {
    int st = state;
    if (f[state] != -1)
        return f[state];

    int fc = st % 4;
    st /= 4;
    int fn = st % 4;
    st /= 4;
    int pc = st % 4;
    st /= 4;
    int pn = st % 4;
    st /= 4;
    for (int i = 0; i < 4; ++i)
        b[i] = st % 8, st /= 8;
    if (accumulate(b, b + 4, 0) == 0) {
        if (pc == fc && pn == fn)
            return f[state] = 1;
        else
            return f[state] = 0;
    }
    int ret = 0;
    for (int i = 0; i < 4; ++i) {
        if (i == pc)
            continue;
        for (int j = 1; j <= 3 && j <= b[i]; ++j) {
            if (j == pn)
                continue;
            b[i] -= j;
            int t = 0;
            for (int k = 3; k >= 0; --k)
                t = t * 8 + b[k];
            t = (((t * 4 + j) * 4 + i) * 4 + fn) * 4 + fc;
            ret += dp(t);
            b[i] += j;
        }
    }
    return f[state] = ret;
}

int main() {
    ios::sync_with_stdio(false);

    int t;
    int n;
    memset(f, -1, sizeof(f));
    cin >> t;
    while (t-- > 0) {
        cin >> n;
        memset(a, 0, sizeof(a));
        for (int i = 0; i < n; ++i)
            cin >> a[i];
        if (accumulate(a, a + n, 0) == 0) {
            cout << "1" << endl;
            continue;
        }
        int ans = 0, k = 0;
        for (int i = 3; i >= 0; --i)
            k = 8 * k + a[i];
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j <= 3 && j <= a[i]; ++j) {
                int t = (((k * 4 + j) * 4 + i) * 4 + j) * 4 + i;
                ans += dp(t);
            }
        }
        cout << ans << endl;
    }

    return 0;
}
