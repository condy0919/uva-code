#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

/*
 * f[t] 表示在t时间内可以最大使用多少时间；
 * num[t] 表示在t时间内可以最多吃多少饼.
 */

int a[2], total;
int f[10001], num[10001];

int main() {
    std::ios_base::sync_with_stdio(false);
    while (cin >> a[0] >> a[1] >> total) {
        memset(f, 0, sizeof(f));
        memset(num, 0, sizeof(num));

        for (int i = 0; i < 2; ++i) {
            for (int t = a[i]; t <= total; ++t) {
                if (f[t] < f[t - a[i]] + a[i]) {
                    f[t] = f[t - a[i]] + a[i];
                    num[t] = num[t - a[i]] + 1;
                } else if (f[t] == f[t - a[i]] + a[i]) {
                    num[t] = max(num[t], num[t - a[i]] + 1);
                }
            }
        }

        if (f[total] == total)
            cout << num[total] << endl;
        else
            cout << num[total] << " " << total - f[total] << endl;
    }
    return 0;
}
