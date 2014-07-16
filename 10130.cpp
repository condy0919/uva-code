#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

/*
 * 对每个人进行一次背包。
 * 注意，背包一次后即可把结果求出来，最后直接用容量去套。
 */

int N, G;
int p[1000], w[1000];
int c[100];
int f[31];

int main()
{
    int T;

    cin >> T;
    while (T-- > 0) {
        cin >> N;
        for (int i = 0; i < N; ++i)
            cin >> p[i] >> w[i];
        cin >> G;
        for (int i = 0; i < G; ++i)
            cin >> c[i];

        fill(f, f + 31, 0);
        for (int j = 0; j < N; ++j)
            for (int kw = 30; kw >= w[j]; --kw)
                f[kw] = max(f[kw], f[kw - w[j]] + p[j]);

        int total_value = 0;
        for (int i = 0; i < G; ++i)
            total_value += f[c[i]];
        cout << total_value << endl;
    }
    return 0;
}
