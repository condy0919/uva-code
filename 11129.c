#include <stdio.h>
#include <math.h>

/*
 * a是当前等差的值，b是当前的值
 */
void gen(int a, int b, int lim, int level)
{
    if (level > 0)
        gen(2 * a, 2 * a + b, lim, level - 1);
    if (b < lim)
        printf(" %d", b);
    if (level > 0)
        gen(2 * a, a + b, lim, level - 1);
}

int main()
{
    int n;
    while (scanf("%d", &n) == 1 && n > 0) {
        printf("%d:", n);
        gen(1, 0, n, 15);
        puts("");
    }
    return 0;
}
