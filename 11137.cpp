#include <iostream>
#include <algorithm>
#include <cstdint>

/*
 * 完全背包,基础dp.
 */

using namespace std;

int coins[21];
uint64_t pay[10001];

void init() {
    for (int i = 1; i <= 21; ++i)
        coins[i - 1] = i * i * i;
}

int main() {
    init();

    fill(pay, pay + 10001, 1);
    for (int i = 1; i < 21; ++i)
        for (int j = 0; j + coins[i] < 10001; ++j)
            pay[j + coins[i]] += pay[j];

    int cost;
    while (cin >> cost)
        cout << pay[cost] << endl;

    return 0;
}
