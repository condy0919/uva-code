#include <stdio.h>
#include <string.h>

int len, n, pos[60];
int cache[60][60];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    while (scanf("%d", &len), len) {
        scanf("%d", &n);
        memset(cache, 0, sizeof(cache));

        pos[0] = 0;
        int i, j, k;
        for (i = 1; i <= n; ++i)
            scanf("%d", &pos[i]);
        pos[++n] = len;

        for (j = 2; j <= n; ++j)
            for (i = 0; i + j <= n; ++i) {
                cache[i][i + j] = 0x7fffffff;
                for (k = i + 1; k < i + j; ++k)
                    cache[i][i + j] = min(cache[i][i + j], cache[i][k] + cache[k][i + j] + pos[i + j] - pos[i]);
            }
        printf("The minimum cutting is %d.\n", cache[0][n]);
    }
    return 0;
}
