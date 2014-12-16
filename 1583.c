#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int T, N;
int f[100000 + 1];

int r(int x) {
    int ret = 0;
    while (x > 0) {
        ret += x % 10;
        x /= 10;
    }
    return ret;
}

int main() {
    int i;
    for (i = 0; i <= 100000; ++i) {
        int t = r(i);
        if (f[i + t] == 0)
            f[i + t] = i;
    }

    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &N);
        printf("%d\n", f[N]);
    }
    return 0;
}
