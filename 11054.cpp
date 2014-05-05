#include <iostream>
#include <algorithm>
#include <cstdint>

using namespace std;

int a[100000];
int64_t solve(int n)
{
    int64_t ret = 0;
    for (int i = 0; i < n - 1; ++i) {
        a[i + 1] += a[i];
        ret += abs(a[i]);
    }
    return ret;
}

int main()
{
    int n;
    while (cin >> n, n) {
        for (int i = 0; i < n; ++i)
            cin >> a[i];
        cout << solve(n) << endl;
    }
    return 0;
}
