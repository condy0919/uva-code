#include <iostream>
#include <vector>
#include <algorithm>

/*
 * gcd(Fn, Fm) = F_gcd(n, m)
 * 则F_gcd(n, m) = 1 = F_1
 * gcd(n, m) = 1
 * 则转换成了素数的问题。
 */

using namespace std;

long double formula(int n) {
    constexpr long double a = 0.5 * (1.0 + sqrt(5));
    constexpr long double b = 0.5 * (1.0 - sqrt(5));
    constexpr long double sqrt5 = sqrt(5);
    return pow(a, n) / sqrt5 - pow(b, n) / sqrt5;
}

vector<int> primes;
bool is_prime[280000 + 1];
#define PRIME false
#define NOT_PRIME true
void sieve() {
    primes.push_back(2);
    primes.push_back(3);

    for (int i = 5, gap = 4; i <= 280000; i += (gap ^= 6)) {
        if (is_prime[i] == PRIME)
            primes.push_back(i);
        for (int j = 0; j < primes.size() && primes[j] * i <= 280000; ++j) {
            is_prime[primes[j] * i] = NOT_PRIME;
            if (i % primes[j] == 0)
                break;
        }
    }
}

int proc(int n) {
#define lg log10l
    return powl(10, fmodl(n * lg((1 + sqrtl(5)) / 2.0) - 0.5 * lg(5), 1) + 8);
#undef lg
}

int main() {
    ios::sync_with_stdio(false);

    sieve();

    int n;
    while (cin >> n) {
        if (n == 1 || n == 2) {
            cout << n + 1 << endl;
            continue;
        }
        if (n <= 14)
            cout << (int)formula(primes[n - 1]) << endl;
        else
            cout << proc(primes[n - 1]) << endl;
    }
    return 0;
}

