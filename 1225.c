#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int T;
int N;
int f[10];

void calc(int x) {
    while (x > 0) {
        ++f[x % 10];
        x /= 10;
    }
}

int main() {
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &N);
        memset(f, 0, sizeof(f));
        int i;
        for (i = 1; i <= N; ++i) {
            int t = i;
            while (t > 0) {
                ++f[t % 10];
                t /= 10;
            }
        }
        printf("%d %d %d %d %d %d %d %d %d %d\n", f[0], f[1], f[2], f[3], f[4],
               f[5], f[6], f[7], f[8], f[9]);
    }
    return 0;
}
