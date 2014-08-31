#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * 简单的分析。
 */

int main() {
    int T;
    int x, k;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d%d", &x, &k);
        if (x / k == (int)ceil(1.0 * x / k)) {
            printf("0 %d\n", k);
        } else {
            printf("%d %d\n", -x, x);
        }
    }
    return 0;
}
