#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cfloat>

/*
 * 集合上的dp。
 * d[s] = min{d[s-{i}-{j}]+|Pij|}
 */

using namespace std;

double x[16], y[16];
double d[1<<16];
int n;
char temp[30];

#define sqr(x) ((x)*(x))
#define dis(a,b) (sqrt(sqr(x[a]-x[b])+sqr(y[a]-y[b])))

int main() {
    int cases = 0;
    while (scanf("%d", &n), n) {
        n *= 2;
        for (int i = 0; i < n; ++i)
            scanf("%*[^ ] %lf %lf", &x[i], &y[i]);

        fill(d, d + (1<<n), DBL_MAX);
        d[0] = 0;
        for (int s = 0; s < (1 << n); ++s) {
            int min;
            for (min = 0; min < n; ++min)
                if (s & (1 << min))
                    break;
            for (int i = min + 1; i < n; ++i)
                if (s & (1 << i))
                    d[s] = std::min(d[s], d[s^(1<<i)^(1<<min)] + dis(i,min));
        }
        printf("Case %d: %.2lf\n", ++cases, d[(1<<n)-1]);
    }
    return 0;
}
