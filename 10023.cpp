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
 * 手工开平方根的办法网上到处都是啊。
 * 优化坑!!!!!
 * 这里需要优化、优化、再优化啊。
 * C++11移动语义拯救一切，再加上一个magic函数、关闭与stdio的同步。
 */

using namespace std;

#define maxn 1005

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
        clean();
        return std::move(*this);
    }

    string str() const {
        string res = "";
        for (int i = 0; i < len; ++i)
            res += (char)(s[i] + '0');
        reverse(res.begin(), res.end());
        if (res == "")
            res = "0";
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
            c.s[c.len++] = x % 10;
            g = x / 10;
        }
        return std::move(c);
    }

    bign operator*(const bign &b) {
        bign c;
        c.len = len + b.len;

        for (int i = 0; i < len; ++i)
            for (int j = 0; j < b.len; ++j)
                c.s[i + j] += s[i] * b.s[j];
        for (int i = 0; i < c.len - 1; ++i) {
            c.s[i + 1] += c.s[i] / 10;
            c.s[i] %= 10;
        }
        c.clean();
        return std::move(c);
    }

    bign operator*(const int b) {
        char v[100];
        bign c;
        sprintf(v, "%d", b);

        c = v;
        return std::move(*this * c);
    }

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
                x += 10;
            }
            c.s[c.len++] = x;
        }
        c.clean();
        return std::move(c);
    }

    // default: current number >= b
    bign operator/(const int b) {
        bign t = *this;
        string result;
        int i, j;
        int64_t divided_number = 0;
        int quotient, remainder;

        for (i = 0, j = t.len - 1; i < j; ++i, --j)
            swap(t.s[i], t.s[j]);

        // find first part
        for (j = 0; j < t.len && divided_number < b; ++j)
            divided_number = 10 * divided_number + t.s[j];
        quotient = divided_number / b;
        remainder = divided_number % b;
        result += (char)(quotient + '0');
        for (int k = j - 1; k >= 0; --k) {
            t.s[k] = remainder % 10;
            remainder /= 10;
        }

        // the remaining part
        for (i = 0; i < t.len && j < t.len; /*++i,*/ ++j) {
            divided_number = 0;
            while (i < t.len && !t.s[i])
                ++i;
            for (int k = i; k <= j; ++k)
                divided_number = 10 * divided_number + t.s[k];
            while (j < t.len && divided_number < b) {
                result += '0';
                divided_number = 10 * divided_number + t.s[++j];
            }
            quotient = divided_number / b;
            remainder = divided_number % b;
            if (j < t.len)
                result += (char)(quotient + '0');

            for (int k = j; k >= i; --k) {
                t.s[k] = remainder % 10;
                remainder /= 10;
            }
        }

        // for (i = result.length() - 1; i >= 0 && result[i] == '0'; --i)
        //	result.erase(i);
        return bign(result.c_str());
    }

    bign operator%(const int b) {
        bign ret;
        ret = *this - (*this / b) * b;
        return ret;
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

    bool operator<=(const bign &b) const { return !(*this > b); }

    bool operator==(const bign &b) const {
        return !(b < *this) && !(*this < b);
    }

    bool operator!=(const bign &b) const { return (b < *this) || (*this < b); }

    bign operator+=(const bign &b) {
        *this = *this + b;
        return std::move(*this);
    }

    bign operator*=(const bign &b) {
        *this = *this * b;
        return std::move(*this);
    }

    bign& magic(int w, int c) {
        for (int i = len + w - 1; i > w - 1; --i)
            s[i] = s[i - w];
        if (w == 1)
            s[0] = c;
        else if (w == 2)
            s[0] = c % 10, s[1] = c / 10;
        len += w;
        clean();
        return *this;
    }
};

istream &operator>>(istream &in, bign &x) {
    string s;

    in >> s;
    x = s.c_str();
    return in;
}

ostream &operator<<(ostream &out, bign &x) {
    out << x.str();
    return out;
}

int main() {
    ios::sync_with_stdio(false);
    bign r, bk;
    string line;
    int n;
    cin >> n;

    while (n-- > 0) {
        cin >> line;
        if (line.length() & 1)
            line = "0" + line;

        r = 0;
        bk = 0;
        for (int i = 0; i < line.length(); i += 2) {
            bk.magic(2, std::stoi(line.substr(i, 2)));
            //bk = bk * 100 + bign(line.substr(i, 2).c_str());
            int t = 0;
            bign store = r * 20;
            for (int j = 9; j >= 0; --j) {
                if ((/*r * 20*/store + j) * j <= bk) {
                    t = j;
                    break;
                }
            }
            bk = bk - (/*r * 20*/store + t) * t;
            r.magic(1, t);
            //r = r * 10 + t;
        }
        cout << r << endl;
        if (n)
            cout << endl;
    }
    return 0;
}

