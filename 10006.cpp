#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

/*
 * 生成素数表，然后再判断是否能够通过fermat_test...
 */

using namespace std;

int n;
bool is_prime[65000] = {false};
int primes[65000 / 10], total = 0;
#define PRIME false
#define NOT_PRIME true

void init_prime_table() {
    for (int i = 6; i < 65000; i += 3)
        is_prime[i] = NOT_PRIME;
    for (int i = 4; i < 65000; i += 2)
        is_prime[i] = NOT_PRIME;

    for (unsigned int i = 5, gap = 4; i < 65000; i += (gap ^= 6)) {
        if (is_prime[i] == PRIME) {
            for (unsigned int j = i * i; j < 65000; j += i)
                is_prime[j] = NOT_PRIME;
        }
    }
    //for (int i = 6; ; i += 6) {
    //    for (int k = 0; k < 2; ++k) {
    //        unsigned int m = i + 2 * k - 1;
    //        if (m >= 65000)
    //            return;
    //        if (is_prime[m] == PRIME) {
    //            for (unsigned int j = m * m; j < 65000; j += m)
    //                is_prime[j] = NOT_PRIME;
    //        }
    //    }
    //}
}

void linear_sieve() {
    primes[total++] = 2;
    primes[total++] = 3;
    for (int i = 5, gap = 4; i <= 65000; i += (gap ^= 6)) {
        if (is_prime[i] == PRIME)
            primes[total++] = i;
        for (int j = 0; j < total && i * primes[j] <= 65000; ++j) {
            is_prime[i * primes[j]] = NOT_PRIME;
            if (i % primes[j] == 0)
                break;
        }
    }
}

unsigned int powmod(unsigned int x, int n, int mod) {
    unsigned int ret = 1;
    while (n > 0) {
        if (n & 1)
            ret = ret * x % mod;
        n >>= 1;
        x = x * x % mod;
    }
    return ret;
}

bool fermat_test(int n) {
    for (int a = 2; a < n; ++a)
        if (powmod(a, n, n) != a)
            return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);

    init_prime_table();
    //linear_sieve();
    while (cin >> n && n > 2 && n < 65000) {
        if (/*!std::binary_search(primes, primes + total, n)*/ is_prime[n] == NOT_PRIME && fermat_test(n))
            cout << "The number " << n << " is a Carmichael number." << endl;
        else
            cout << n << " is normal." << endl;
    }

    return 0;
}
