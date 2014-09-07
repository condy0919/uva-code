#include <cstdio>

/*
 * 一开始直接组合分析了，得到C(2n-2, n-2) * (1/2)^(2n-2)...当然会和样例不一样啦！
 * 后来一想，原来是当A物品用完后，就不用掷骰子了。
 * 从反而考虑的话，就一直会掷骰子到最后，于是可以这样来。
 * 很容易可以得到p[n] = C(2n-2,n-1)*(1/2)^(2n-2)..
 * 扔进W|A, 得到p[n] / p[n-1] = (2n-3) / (2n - 2).
 * 同时base case为p[1] = 1.于是有了递推关系就不会溢出了。
 */

using namespace std;

int main() {
    int N, n;
    int T;

    const int SIZE = 100000 / 2 + 1;
    double p[SIZE];
    p[1] = 1;
    for (int i = 2; i < SIZE; ++i)
        p[i] = p[i - 1] * (2 * i - 3) / (2 * i - 2);

    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &N);
        printf("%.4lf\n", 1 - p[N / 2]);
    }

    return 0;
}
