#include <stdio.h>
#include <string.h>

#define maxn 65000
#define maxd 8

int d, s, b;
char raid[maxd][maxn];
char ans[maxn];
int parity;

int check() {
    for (int i = 0; i < b; ++i) {
        for (int j = 0; j < s; ++j) {
            int sum = 0, miss = 0;
            for (int k = 0; k < d; ++k) {
                if (raid[k][s * i + j] == 'x')
                    ++miss;
                else
                    sum += raid[k][s * i + j] - '0';
            }
            if (miss > 1)
                return 0;
            if (miss == 0 && sum % 2 != parity)
                return 0;
            for (int k = 0; k < d; ++k) {
                if (raid[k][s * i + j] == 'x')
                    raid[k][s * i + j] = (sum % 2 != parity) ? '1' : '0';
            }
        }
    }
    return 1;
}

int main() {
    int cases = 0;

    while (scanf("%d%d%d\n", &d, &s, &b) == 3 && d) {
        printf("Disk set %d is ", ++cases);

        memset(ans, 0, sizeof(ans));
        memset(raid, 0, sizeof(raid));
        scanf("%c\n", &parity);
        parity = (parity == 'O' ? 1 : 0);
        for (int i = 0; i < d; ++i)
            scanf("%s", raid[i]);

        if (!check()) {
            puts("invalid.");
            continue;
        }
        printf("valid, contents are: ");
        for (int i = 0; i < b; ++i) {
            for (int j = 0; j < d; ++j) {
                for (int k = 0; k < s; ++k) {
                    if (j != i % d)
                        strncat(ans, &raid[j][s * i + k], 1);
                }
            }
        }
        while (strlen(ans) % 4)
            strncat(ans, "0", 1);
        for (int i = 0, len = strlen(ans); i < len; i += 4) {
            int ch = 0;
            for (int j = 0; j < 4; ++j)
                ch = 2 * ch + (ans[i + j] - '0');
            printf("%X", ch);
        }
        puts("");
    }
    return 0;
}
