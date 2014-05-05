#include <stdio.h>
#include <math.h>
#include <stdint.h>
#define eps (1e-6)
int main() {
    int64_t m, p, a, b;
    while (scanf("%lld%lld%lld%lld", &m, &p, &a, &b) == 4) {
        int64_t x, r;
        double ans = 0.0;
        
        if (b > 0) {
            x = (m - b) / (a + 1);
            r = (m - b) % (a + 1);
            ans = pow(a, p * 1.0) * b + x * (a + pow(a, p * 1.0));
            if (r > 1)
                ans += (r - 1) + pow(r - 1, p * 1.0);
            ans /= pow(sqrt(a), p * 1.0);
        } else {
            int64_t rr = m + a * b;
            x = rr / (a + 1);
            r = rr % (a + 1);
            ans = -b * a + x * (a + pow(a, p * 1.0));
            if (r > 1)
                ans += (r - 1) + pow(r - 1, p * 1.0);
            ans /= pow(sqrt(a), p * 1.0);
        }
        printf("%lld\n", (int64_t)(ans + 0.5 + eps));
    }
    return 0;
}
