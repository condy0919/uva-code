#include <stdio.h>
#include <stdint.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))

/*
 * http://hi.baidu.com/krdefndrsbbekmd/item/389c8d4d8ae1cfe11381daba
 * http://blog.csdn.net/shiqi_614/article/details/7001949
 * ^ 上面是有关Ferrers图相关的东西。
 * 利用Ferrers图的性质来做。
 * 即将k个硬币凑成c元钱 -> c元钱可由最大面值为k的硬币凑成。
 * 则f[c][k] = f[c - k][k]      + f[c][k - 1];
 *             ^ 用1个k面值硬币   ^ 没有用
 */
int64_t f[301][301];
char line[32];
int N, L1, L2;

int main() {
    int i, j;

    f[0][0] = 1;
    for (i = 0; i <= 300; ++i)
        for (j = 1; j <= 300; ++j) {
            if (i >= j)
                f[i][j] += f[i - j][j];
            if (j >= 1)
                f[i][j] += f[i][j - 1];
        }

    while (fgets_unlocked(line, 31, stdin)) {
        L1 = L2 = -1;
        sscanf(line, "%d%d%d", &N, &L1, &L2);
        L1 = min(L1, 300);
        L2 = min(L2, 300);
        if (L1 == -1) {
            printf("%lld\n", f[N][N]);
        } else if (L2 == -1) {
            printf("%lld\n", f[N][L1]);
        } else if (L1 == 0) {
            printf("%lld\n", f[N][L2]);
        } else {
            printf("%lld\n", f[N][L2] - f[N][L1 - 1]);
        }
    }
    return 0;
}
