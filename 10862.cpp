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

using namespace std;

/*
 * 一开始死规律，结果显然被坑，后经UVa OJ Board上某人提醒：`think about fibonacci numbers...`
 * 则看出来了是f[n] = fib[2 * n - 1];
 */

#define maxn 93

#define BASE 1000000000

struct bign {
    int len, s[maxn];

    bign() {
        memset(s, 0, sizeof(s));
        len = 1;
    }

    bign(int num) { *this = num; }

    bign(const char *num) { *this = num; }

    bign operator=(int num) {
        char s[maxn];
        sprintf(s, "%d", num);
        *this = s;
        return std::move(*this);
    }

    bign operator=(const char *num) {
        len = strlen(num);
        for (int i = 0; i < len; ++i)
            s[i] = num[len - 1 - i] - '0';
        return std::move(*this);
    }

    string str() const {
        string res = "";
        char buf[12] = "";
        for (int i = 0; i < len - 1; ++i) {
            sprintf(buf, "%09d", s[i]);
            res = std::move(buf + res);
            //res += (char)(s[i] + '0');
        }
        sprintf(buf, "%d", s[len - 1]);
        res = buf + res;
        if (res == "")
            res = "0";
        //std::reverse(res.begin(), res.end());
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
};

ostream &operator<<(ostream &out, bign &x) {
    out << x.str();
    return out;
}

bign fib[4000] = {1, 1, 2};

int main() {
    for (int i = 3; i < 4000; ++i)
        fib[i] = fib[i - 1] + fib[i - 2];

    int n;
    while (cin >> n, n)
        cout << fib[2 * n - 1] << endl;

    return 0;
}

