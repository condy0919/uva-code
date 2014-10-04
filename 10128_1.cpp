#include <iostream>
#include <algorithm>

/*
 * 这个递推思路确实不错..
 * http://www.cnblogs.com/staginner/archive/2011/12/17/2291004.html
 */

using namespace std;

long long f[14][14][14];

int main() {
    ios::sync_with_stdio(false);

    f[1][1][1] = 1;
    for (int i = 2; i < 14; ++i)
        for (int j = 1; j < 14; ++j)
            for (int k = 1; k < 14; ++k)
                f[i][j][k] = f[i - 1][j - 1][k] + f[i - 1][j][k - 1] + (i - 2) * f[i - 1][j][k];


    int T;
    int N, L, R;
    cin >> T;
    while (T-- > 0) {
        cin >> N >> L >> R;
        cout << f[N][L][R] << endl;
    }

    return 0;
}
