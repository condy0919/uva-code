#include <iostream>

using namespace std;

/*
 * 改成long long就过了..
 * S(10n) = 45 * n + S(n).
 * 其他情况转化为此情况.
 */

long long f(long long n) {
    return n * (n + 1) / 2;
}

long long S(long long n, long long acc = 0) {
    if (n <= 0)
        return acc;
    else if (n % 10 == 0)
        return S(n / 10, acc + 45 * (n / 10));
    else
        return S(n - n % 10, acc + f(n % 10));
}

int main() {
    ios::sync_with_stdio(false);

    long p, q;
    while (cin >> p >> q, p >= 0 && q >= 0) {
        cout << S(q) - S(p - 1) << endl;
    }

    return 0;
}
