#include <stdio.h>
#include <math.h>
#define MAXSIZE 1000000

int zeros[MAXSIZE];
double p[MAXSIZE];
int ch;

int scand(int* x) {
    *x = 0;
    while ((ch = getchar_unlocked()) != '\n' && ch != EOF)
        *x = 10 * *x + (ch - '0');
    return ch == '\n' ? 1 : EOF;
}

int main() {
    double s = 0.0;
    long long i;
    for (i = 1; i < MAXSIZE; ++i) {
        p[i] = 1.0 - (1.0 - p[i - 1]) * (1 - 1.0 / (i * (i + 1)));
        s += log10(1.0 * i * (i + 1.0)); /* 照理来说i会被转换成double的，不知道为什么当i的类型为int时总是有错误..*/
        zeros[i] = s;
    }

    int N;
    while (scand(&N) != EOF)
        printf("%.6f %d\n", p[N], zeros[N]);

    return 0;
}
