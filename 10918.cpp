#include <iostream>
#include <algorithm>

/*
 * 参考http://www.cnblogs.com/staginner/archive/2011/12/16/2290020.html
 */

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int f[31] = {1, 0, 3, 0};
    for (int i = 4; i < 31; ++i)
        f[i] = 4 * f[i - 2] - f[i - 4];

    int n;
    while (cin >> n, n != -1)
        cout << f[n] << endl;

    return 0;
}
