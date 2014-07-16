#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

/*
 * f[i]表示在剩余i个元素的情况选手是否会胜利.
 * 如果可行移除下f[i - rem[k]] 都为true, 则当前先手必定输.
 * 否则只要有一个f[i - rem[k]] 为false，则当前先手即可用此种方法赢.
 */

#define N 1000000

int n;
int m, rem[10];
bool f[N + 1];

int main() {
    while (cin >> n >> m) {
        for (int i = 0; i < m; ++i)
            cin >> rem[i];
        memset(f, 0, sizeof(f));
        f[1] = true;
        for (int i = 2; i <= n; ++i) {
            bool flag = false;
            for (int j = 0; j < m; ++j)
                if (i - rem[j] >= 0 && !f[i - rem[j]]) {
                    flag = true;
                    break;
                }
            f[i] = flag;
        }
        cout << (f[n] ? "Stan wins" : "Ollie wins") << endl;
    }
    return 0;
}
