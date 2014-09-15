#include <iostream>
#include <algorithm>
#include <initializer_list>
#include <numeric>
#include <cstring>
#include <cstdint>
#include <cassert>

/*
 * f[n] = f[n-1] + f[n-2] + 1
 */

using namespace std;

template<size_t N>
struct matrix {
    int a[N][N];

    matrix() { memset(a, 0, sizeof(a)); }

    matrix(const matrix &rhs) { *this = rhs; }

    matrix(std::initializer_list<int> &&lst) {
        assert(lst.size() == N * N);
        int *p = (int *)a;
        for (const auto &i : lst)
            *p++ = i;
    }

    matrix &operator=(const matrix &rhs) {
        memcpy(a, rhs.a, sizeof(a));
        return *this;
    }

    const int *operator[](size_t idx) const { return a[idx]; }
    int *operator[](size_t idx) { return a[idx]; }

    matrix operator*(const matrix &rhs) const {
        const matrix &lhs = *this;
        matrix ret;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                for (int k = 0; k < N; ++k)
                    ret[i][j] += lhs[i][k] * rhs[k][j];
        return std::move(ret);
    }

    matrix operator%(int mod) {
        matrix ret = *this;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                ret[i][j] %= mod;
        return std::move(ret);
    }
};

matrix<3> powmod(matrix<3> x, uint64_t n, int mod) {
    matrix<3> ret = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    while (n > 0) {
        if (n & 1)
            ret = ret * x % mod;
        n >>= 1;
        x = x * x % mod;
    }
    return std::move(ret);
}

int main() {
    ios::sync_with_stdio(false);

    uint64_t n;
    int b;
    matrix<3> factor = {1, 0, 0, 0, 0, 1, 1, 1, 1};
    for (int cases = 0; cin >> n >> b, n || b; ++cases) {
        cout << "Case " << 1 + cases << ": " << n << " " << b << " ";
        if (n == 0 || n == 1) {
            cout << "1" << endl;
            continue;
        }
        matrix<3> ans = powmod(factor, n - 1, b);
        cout << std::accumulate(ans[2], ans[2] + 3, 0) % b << endl;
    }

    return 0;
}
