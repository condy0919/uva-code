#include <stdio.h>
#include <string.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))

char s[1005];
int f[1005][1005];
int T, len;
int i, j, k;

int main() {
    scanf("%d", &T);
    getchar_unlocked();
    while (T-- > 0) {
        fgets_unlocked(s + 1, 1005, stdin);
        len = strlen(s + 1) - 1;

        memset(f, 0, sizeof(f));
        for (i = 1; i <= len; ++i)
            f[i][i] = 1;

        for (k = 1; k <= len; ++k)
            for (i = 1; i + k <= len; ++i) {
                j = i + k;
                if (s[i] == s[j])
                    f[i][j] = f[i + 1][j - 1] + 2;
                else
                    f[i][j] = max(f[i + 1][j], f[i][j - 1]);
            }
        printf("%d\n", f[1][len]);
    }
    return 0;
}
