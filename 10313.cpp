#include <cstdio>
#include <algorithm>
#include <stdint.h>

using namespace std;

int main() {
    int N, L1, L2;
    char line[128];
    int64_t f[305][305] = {0};

    f[0][0] = 1;
    for (int i = 1; i <= 300; ++i)
        for (int c = i; c <= 300; ++c)
            for (int n = 1; n <= 300; ++n)
                f[c][n] += f[c - i][n - 1];

    while (fgets_unlocked(line, 127, stdin)) {
        L1 = L2 = -1;
        sscanf(line, "%d%d%d", &N, &L1, &L2);
        L1 = min(L1, 300);
        L2 = min(L2, 300);
        int64_t ans = 0;
        if (L1 == -1) {
            for (int i = 0; i <= N; ++i)
                ans += f[N][i];
        } else if (L2 == -1) {
            for (int i = 0; i <= L1; ++i)
                ans += f[N][i];
        } else {
            for (int i = L1; i <= L2; ++i)
                ans += f[N][i];
        }
        printf("%lld\n", ans);
    }
    return 0;
}
