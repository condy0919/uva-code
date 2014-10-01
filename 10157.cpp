#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <stdint.h>

/*
 * 太高优化会错啊..
 * 参考: http://www.cnblogs.com/staginner/archive/2011/12/16/2290795.html
 */

using namespace std;

#define BASE 10000
#define GAP 4

#define maxn 24

struct bign {
    int len, s[maxn];

    bign() {
        memset(s, 0, sizeof(s));
        len = 1;
    }

    bign(int num) { *this = num; }

    bign operator=(int num) {
        len = 0;
        do {
            s[len++] = num % BASE;
            num /= BASE;
        } while (num > 0);
        return std::move(*this);
    }

    string str() const {
        string res = "";
        for (int i = 0; i < len - 1; ++i) {
            res += (char)(s[i] / 1 % 10 + '0');
            res += (char)(s[i] / 10 % 10 + '0');
            res += (char)(s[i] / 100 % 10 + '0');
            res += (char)(s[i] / 1000 % 10 + '0');
#if GAP > 4
            res += (char)(s[i] / 10000 % 10 + '0');
            res += (char)(s[i] / 100000 % 10 + '0');
            res += (char)(s[i] / 1000000 % 10 + '0');
            res += (char)(s[i] / 10000000 % 10 + '0');
#endif
        }
        int t = s[len - 1];
        while (t > 0) {
            res += (char)(t % 10 + '0');
            t /= 10;
        }
        if (res == "")
            res = "0";
        std::reverse(res.begin(), res.end());
        return std::move(res);
    }

    void clean() {
        while (len > 1 && !s[len - 1])
            --len;
    }

    bign operator+(const bign &b) const {
        bign c;
        c.len = 0;

        for (int i = 0, g = 0; g || i < max(len, b.len); ++i) {
            int x = g;
            if (i < len)
                x += s[i];
            if (i < b.len)
                x += b.s[i];
            c.s[c.len++] = x % BASE;
            g = x / BASE;
        }
        return std::move(c);
    }

    bign operator*(const bign &b) {
        bign c;
        c.len = len + b.len;

        for (int i = 0; i < len; ++i)
            for (int j = 0; j < b.len; ++j) {
                c.s[i + j] += s[i] * b.s[j];
                c.s[i + j + 1] += c.s[i + j] / BASE;
                c.s[i + j] %= BASE;
            }
        for (int i = 0; i < c.len - 1; ++i) {
            c.s[i + 1] += c.s[i] / BASE;
            c.s[i] %= BASE;
        }
        c.clean();
        return std::move(c);
    }

    bign operator*(const int b) { return std::move(*this * bign(b)); }

    bign operator-(const bign &b) {
        bign c;
        c.len = 0;

        for (int i = 0, g = 0; i < len; ++i) {
            int x = s[i] - g;
            if (i < b.len)
                x -= b.s[i];
            if (x >= 0)
                g = 0;
            else {
                g = 1;
                x += BASE;
            }
            c.s[c.len++] = x;
        }
        c.clean();
        return std::move(c);
    }

    bool operator<(const bign &b) const {
        if (len != b.len)
            return len < b.len;
        for (int i = len - 1; i >= 0; --i)
            if (s[i] != b.s[i])
                return s[i] < b.s[i];
        return false;
    }

    bool operator<(const int x) const { return *this < bign(x); }

    bool operator>(const bign &b) const { return b < *this; }

    bool operator<=(const bign &b) const { return !(b > *this); }

    bool operator==(const bign &b) const {
        return !(b < *this) && !(*this < b);
    }

    bool operator!=(const bign &b) const { return (b < *this) || (*this < b); }

    bign& operator+=(const bign &b) {
        *this = *this + b;
        return *this;
    }

    bign& operator*=(const bign &b) {
        *this = *this * b;
        return *this;
    }
};

ostream &operator<<(ostream &out, bign &&x) {
    out << x.str();
    return out;
}

bign f[151][151];

int main() {
    ios::sync_with_stdio(false);

    fill_n(f[0], 151, 1);
    for (int i = 1; i <= 150; ++i)
        for (int j = 1; j <= 150; ++j)
            for (int k = 0; k < i; ++k)
                f[i][j] += f[k][j - 1] * f[i - k - 1][j];

    int n, d;
    while (cin >> n >> d) {
        if (n & 1) {
            cout << "0" << endl;
            continue;
        }
        n >>= 1;
        cout << f[n][d] - f[n][d - 1] << endl;
    }
    return 0;
}
