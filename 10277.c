#include <stdio.h>
#include <math.h>

typedef unsigned long long ULL;

ULL gcd(ULL a, ULL b) {
    while (b) {
        ULL r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main() {
    ULL p, q;
    ULL r, b;
    while (scanf("%llu%llu", &p, &q), p || q) {
        if (p == q) {
            puts("2 0");
            continue;
        } else if (p == 0) {
            puts("0 2");
            continue;
        }

        ULL c = gcd(p, q);
        p /= c;
        q /= c;

        ULL s;
        int flag = 0;
        for (s = 2; s <= 50000; ++s) {
            if (s * (s - 1) % q)
                continue;
            ULL k = s * (s - 1) / q;
            ULL temp = sqrt(k * p);
            if (temp * (temp + 1) == k * p) {
                r = temp + 1;
                b = s - r;
                flag = 1;
                break;
            }
        }
        if (flag)
            printf("%llu %llu\n", r, b);
        else
            puts("impossible");
    }
    return 0;
}
