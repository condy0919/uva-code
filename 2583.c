#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) < (b)) ? (b) : (a))

char s[82];
int left[82], right[82];

int less(int s1, int e1, int s2, int e2) {
    while (s[s1] == '0')
        ++s1;
    while (s[s2] == '0')
        ++s2;
    if (e1 - s1 != e2 - s2)
        return e1 - s1 < e2 - s2;
    while (s1 < e1) {
        if (s[s1] != s[s2])
            return s[s1] < s[s2];
        ++s1, ++s2;
    }
    return 0;
}

void print(int n) {
    int i, p = right[0];
    for (i = 0; i < n; p = right[p]) {
        while (i < p && i < n)
            putchar_unlocked(s[i++]);
        if (i < n)
            putchar_unlocked(',');
    }
    puts("");
}

int main() {
    while (fgets_unlocked(s, 82, stdin)) {
        int len = strlen(s);
        s[len--] = '\0';
        if (len == 1 && s[0] == '0')
            break;

        memset(left, 0, sizeof(left));
        memset(right, 0, sizeof(right));
        /*
         * 3 5 4 6
         *   ^j  ^i
         */
        int i, j;
        for (i = 1; i < len; ++i)
            for (j = 0; j < i; ++j)
                if (less(left[j], j + 1, j + 1, i + 1))
                    left[i] = max(left[i], j + 1);

        int tlen = left[len - 1];
        right[tlen + 1] = right[tlen] = len;

        for (i = tlen - 1; s[i] == '0' && i >= 0; --i)
            right[i] = len;

        for (i = tlen - 1; i >= 0; --i)
            for (j = i; j <= tlen; ++j)
                if (less(i, j, j, right[j]))
                    right[i] = max(right[i], j);
        print(len);
    }
    return 0;
}
