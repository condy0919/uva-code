#include <cstdio>
#include <cmath>

/*
 * 原来是要逆推的啊，完全没有想到。。
 * 题解看这里:http://www.cnblogs.com/staginner/archive/2011/12/14/2287150.html
 */

#define eps (1e-9)

using namespace std;

int expe[31] = {1};

double solve(int n, double t) {
    if (fabs(t - 1) < eps)
        return expe[n];

    double ans = expe[n];
    for (int i = n - 1; i >= 0; --i) {
        double ep = expe[i] / ans;
        if (t >= ep)
            ans = (1 + t) / 2.0 * ans;
        else
            ans = (ep-t)/(1.0-t)*expe[i] + (1-ep)/(1.0-t)*(1+ep)/2.0*ans;
    }
    return ans;
}

int main() {
    for (int i = 1; i < 31; ++i)
        expe[i] = expe[i - 1] * 2;

    int n;
    double t;
    while (scanf("%d %lf", &n, &t), n || fabs(t) > eps)
        printf("%.3lf\n", solve(n, t));

    return 0;
}
