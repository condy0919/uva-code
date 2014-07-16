#include <stdio.h>
#include <stdint.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))

int main() {
    int N, L1, L2;
    char line[32];
    int64_t f[301][301] = {0};
    int i, c, n;

    f[0][0] = 1;
    for (i = 1; i <= 300; ++i)
        for (c = i; c <= 300; ++c)
            for (n = 1; n <= 300; ++n)
                f[c][n] += f[c - i][n - 1];

    while (fgets_unlocked(line, 31, stdin)) {
        L1 = L2 = -1;
        sscanf(line, "%d%d%d", &N, &L1, &L2);
        L1 = min(L1, 300);
        L2 = min(L2, 300);
        int64_t ans = 0;
        if (L1 == -1)
            for (i = 0; i <= N; ++i)
                ans += f[N][i];
        else if (L2 == -1)
            for (i = 0; i <= L1; ++i)
                ans += f[N][i];
        else
            for (i = L1; i <= L2; ++i)
                ans += f[N][i];
        printf("%lld\n", ans);
    }
    return 0;
}
