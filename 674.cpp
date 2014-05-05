#include <iostream>
#include <algorithm>

using namespace std;

/*
 * 一开始写了个5 * 7489^2的dp来初始化。
 * 可以保存以前j + k * coins[i]的和于a[j + (k - 1) * coins[i]], 这样可以一遍循环就可以了。
 */

#define N 8000

int a[N], n;
const int coins[5] = {1,5,10,25,50};

int main() {
    fill(a, a + N, 1);
    for (int i = 1; i < 5; ++i)
        for (int j = 0; j <= 7489; ++j)
            a[j + coins[i]] += a[j];
    while (cin >> n)
        cout << a[n] << endl;
    return 0;
}
