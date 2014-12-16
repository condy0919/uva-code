#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char s[82];
int T;
int len;

int get_n(int idx) {
    int ret = 0;
    while (idx < len && isdigit(s[idx])) {
        ret = ret * 10 + (s[idx] - '0');
        ++idx;
    }
    return ret ? ret : 1;
}

double get_mass(int ch) {
    switch (ch) {
    case 'C':
        return 12.01;
    case 'H':
        return 1.008;
    case 'O':
        return 16.00;
    case 'N':
        return 14.01;
    }
    return 0.0;
}

int main() {
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%s", s);
        len = strlen(s);
        int i = 0;
        double ans = 0;
        for (i = 0; i < len; ++i) {
            if (s[i] == 'C' || s[i] == 'H' || s[i] == 'O' || s[i] == 'N') {
                int n = get_n(i + 1);
                ans += n * get_mass(s[i]);
            }
        }
        printf("%.3f\n", ans);
    }
    return 0;
}
