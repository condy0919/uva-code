#include <cstdio>

/*
 * long double就AC了。。。
 * 见http://acm.uva.es/board/viewtopic.php?f=20&t=2399&sid=99a14843feb8617d2852c639d5e5dcd2&start=15
 */

using namespace std;

int main() {
    int p, q, r, s;
    while (scanf("%d%d%d%d", &p, &q, &r, &s) == 4) {
        long double ans = 1.0;
        for (int i = 1; i <= p - q || i <= r - s; ++i) {
            if (i <= p - q)
                ans = ans * (q + i) / i;
            if (i <= r - s)
                ans = ans / (s + i) * i;
        }
        printf("%.5llf\n", ans);
    }
    return 0;
}
