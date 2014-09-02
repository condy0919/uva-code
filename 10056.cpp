#include <cstdio>
#include <algorithm>
#include <cmath>

#define pi (acos(-1.0))
#define eps (1e-9)
#define inf 0x7f7f7f7f

using namespace std;

/*
 * 忘记避免Nan了。。
 */

double fun(int N, double p, int I) {
    if (fabs(p) < eps)
        return 0;
    double ret = p * pow(1 - p, I - 1) / (1 - pow(1 - p, N));
    return ret;
}

int main() {
    int T;
    int N, I;
    double p;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d %lf %d", &N, &p, &I);
        printf("%.4lf\n", fun(N, p, I));
    }

    return 0;
}
