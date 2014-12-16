#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int T;
int len;
char s[101];

int less(int x, int y) {
    int k = len;
    while (k-- > 0) {
        if (s[x] > s[y])
            return 0;
        if (s[x] < s[y])
            return 1;
        x = (x + 1) % len;
        y = (y + 1) % len;
    }
    return 0;
}

int main() {
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%s", s);
        len = strlen(s);
        int ans = 0, i;
        for (i = 1; i < len; ++i)
            if (less(i, ans))
                ans = i;
        for (i = ans; i < len; ++i)
            putchar(s[i]);
        for (i = 0; i < ans; ++i)
            putchar(s[i]);
        puts("");
    }
    return 0;
}
