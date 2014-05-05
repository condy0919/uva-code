#include <stdio.h>
#include <math.h>

/*
 * C写得就是快。对每个人将分到的面积进行二分，注意处理eps.
 */

#define pi (acos(-1.0))
#define eps 1e-4
#define max(a, b) ((a) > (b) ? (a) : (b))

double a[10000];
int N, T, F, r;
int i;

int P(double guess, int f) {
    int pieces = 0;
    for (i = 0; i < N; ++i)
        pieces += (int)(a[i] / guess);
    return pieces >= f;
}

int main() {
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d%d", &N, &F);
        double hi = 0.0, lo = 0.0, mid;
        for (i = 0; i < N; ++i) {
            scanf("%d", &r);
            a[i] = pi * r * r;
            hi = max(hi, a[i]);
        }
        while (hi - lo > eps) {
            mid = (hi + lo) / 2.0;
            if (P(mid, F + 1))
                lo = mid;
            else
                hi = mid;
        }
        printf("%.4lf\n", lo);
    }
    return 0;
}
