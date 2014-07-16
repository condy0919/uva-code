#include <stdio.h>
#include <string.h>

/*
 * 基本的dp。
 */

int len, n, pos[60];
int cache[60][60];

int min(int a, int b) {
    return a < b ? a : b;
}

int dp(int s, int e) {
    if (s + 1 >= e)
        return 0;
    if (cache[s][e])
        return cache[s][e];

    int ret = pos[e] - pos[s], _min = 0x7fffffff;
    if (s + 1 >= e)
        return cache[s][e] = 0;
    int i;
    for (i = s + 1; i < e; ++i)
        _min = min(_min, dp(s, i) + dp(i, e));
    return cache[s][e] = ret + _min;
}

int main() {
    int v;
    while (scanf("%d", &len), len) {
        scanf("%d", &n);
        memset(cache, 0, sizeof(cache));

        pos[0] = 0;
        int i;
        for (i = 1; i <= n; ++i)
            scanf("%d", &pos[i]);
        pos[++n] = len;
        printf("The minimum cutting is %d.\n", dp(0, n));
    }
    return 0;
}
