#include <stdio.h>
#include <stdint.h>

/*
 * 源代码出处在这里。
 * http://mypaper.pchome.com.tw/zerojudge/post/1323604436
 * 其动规方程是f[c][s]代表在最多c大小的背包下选择s个物品是否能够达到这个状态。
 * 则f[c][s] 可由f[c-w[i]][s-1]推得。需要注意的是，这里的推导方向很重要，必须由
 * f[高][s] 高->低推导，否则在计算f[高][s]时会由于f[低][s-1]正好在当次中得到，因而会发生错误。
 * ^ 上面是基本的dp，时间花费是巨大的。
 *
 * 如上述链接中所讲的那样，由于人数最多只有50个，可以在1个int64_t中存放下来。
 * 故f[i] = [0.1.2.....63] f[i]的每1bit的状态代表i大小下那个人数的状态是否可达。
 * f[c] 可由 f[c-w[i]]推得。因为是多选择了一个人，而且会继承以前的状态，故而可直接f[c-w[i]]直接左移1位。
 */

int main() {
    int t, n, i, j;
    int w[100];
    scanf("%d", &t);
    while (t-- > 0) {
        scanf("%d", &n);
        int sum = 0;
        for (i = 0; i < n; ++i)
            scanf("%d", &w[i]), sum += w[i];
        int hsum = sum / 2, hn = n / 2;
        int64_t dp[hsum + 1];
        for (i = 0; i <= hsum; ++i)
            dp[i] = 0;
        dp[0] = 1;
        for (i = 0; i < n; ++i)
            for (j = hsum; j >= w[i]; --j)
                dp[j] |= dp[j - w[i]] << 1LL;

        if (n % 2)
            while (!(dp[hsum]&(1LL<<hn)) && !(dp[hsum]&(1LL<<(hn+1))))
                --hsum;
        else
            while (!(dp[hsum]&(1LL<<hn)))
                --hsum;
        printf("%d %d\n", hsum, sum - hsum);
        if (t)
            puts("");
    }
    return 0;
}
