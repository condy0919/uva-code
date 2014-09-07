#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <bitset>
#include <utility>
#include <functional>
#include <numeric>
#include <limits>
#include <cmath>
#include <cctype>
#include <cstring>

#define pi (acos(-1.0))
#define eps (1e-9)
#define inf 0x7f7f7f7f

using namespace std;

typedef unsigned long long ULL;

template<typename T>
T gcd(T a, T b) {
    while (b) {
        T r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);

    ULL p, q;
    ULL r, b;
    while (cin >> p >> q, p || q) {
        // 总是错在特殊情况下...
        if (p == q) {
            cout << "2 0" << endl;
            continue;
        } else if (p == 0) {
            cout << "0 2" << endl;
            continue;
        }
        // simplify
        ULL c = gcd(p, q);
        p /= c;
        q /= c;

        bool flag = false;
        for (ULL s = 2; s <= 50000; ++s) {
            if (s * (s - 1) % q)
                continue;
            ULL k = s * (s - 1) / q;
            ULL temp = sqrt(k * p);
            if (temp * (temp + 1) == k * p) {
                r = temp + 1;
                b = s - r;
                flag = true;
                break;
            }
        }
        if (flag)
            cout << r << " " << b << endl;
        else
            cout << "impossible" << endl;
    }

    return 0;
}
