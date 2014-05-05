#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;

#define pi (acos(-1.0))
#define eps 1e-4

double a[10000];
int N;

bool P(double guess, int F) {
    int pieces = 0;
    for (int i = 0; i < N; ++i)
        pieces += int(a[i] / guess);
    return pieces >= F;
}

int main() {
    int T;
    int F;
    int r;
    
    cin >> T;
    while (T-- > 0) {
        cin >> N >> F;
        double hi = 0.0, lo = 0.0, mid;
        for (int i = 0; i < N; ++i) {
            cin >> r;
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
