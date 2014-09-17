#include <iostream>
#include <algorithm>
#include <stdint.h>

#define pi (acos(-1.0))
#define eps (1e-9)
#define inf 0x7f7f7f7f

/*
 * 找规律。。
 */

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int64_t n;
    while (cin >> n, n >= 0)
        cout << (n * n + n) / 2 + 1 << endl;

    return 0;
}
