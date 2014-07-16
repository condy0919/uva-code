#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stdint.h>

using namespace std;

int64_t f[30001], n, m;
const static int coins[5] = {1,5,10,25,50};

int main() {
    f[0] = 1;
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j + coins[i] < 30001; ++j)
            f[j + coins[i]] += f[j];

    while (cin >> n) {
        m = f[n];
        if (m == 1)
            printf("There is only 1 way to produce %d cents change.\n", n);
        else
            printf("There are %lld ways to produce %d cents change.\n", m, n);
    }
    return 0;
}
