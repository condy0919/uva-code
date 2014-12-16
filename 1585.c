#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int T;
int ch;
int len;
char s[90];

int main() {
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%s", s);
        len = strlen(s);
        int i;
        int seq = 0, ans = 0;
        for (i = 0; i < len; ++i) {
            if (s[i] == 'O')
                ++seq;
            else
                seq = 0;
            ans += seq;
        }
        printf("%d\n", ans);
    }
    return 0;
}
