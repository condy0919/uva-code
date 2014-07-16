#include <stdio.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))

int solve(int c, int n1, int n5, int n10) {
    int ret = 0;
    if (c > n5 + n10) {
        ret += min(c - n5 - n10, n10) * 3;
        n5 += min(c - n5 - n10, n10);
    }
    ret += min(n10, c);
    c -= min(n10, c);
    if (c == 0)
        return ret;
    int x = n5 - c;
    if (x >= c) {
        return ret + 2 * c;
    } else if (x > 0) {
        ret += 2 * x;
        c -= x;
        n5 -= 2 * x;
    }
    ret += 4 * n5;
    c -= n5;
    ret += 8 * c;
    return ret;
}

int main() {
    int t;
    int c, n1, n5, n10;
    scanf("%d", &t);
    while (t-- > 0) {
        scanf("%d %d %d %d", &c, &n1, &n5, &n10);
        printf("%d\n", solve(c, n1, n5, n10));
    }
    return 0;
}
