#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct cmd {
    char c[3];
    union {
        struct {
            int r1, c1, r2, c2;
        };
        struct {
            int A, x[10];
        };
    } un;
};

cmd ops[10000];
int n;
int row, col;

bool doit(int& r, int& c) {
    for (int i = 0; i < n; ++i) {
        if (ops[i].c[0] == 'E') { // exchange
            if (ops[i].un.r1 == r && ops[i].un.c1 == c) {
                r = ops[i].un.r2;
                c = ops[i].un.c2;
            } else if (ops[i].un.r2 == r && ops[i].un.c2 == c) {
                r = ops[i].un.r1;
                c = ops[i].un.c1;
            }
        } else {
            int dr = 0, dc = 0;
            for (int j = 0; j < ops[i].un.A; ++j) {
                int x = ops[i].un.x[j];
                if (ops[i].c[0] == 'I') {
                    if (ops[i].c[1] == 'R' && x <= r)
                        ++dr;
                    if (ops[i].c[1] == 'C' && x <= c)
                        ++dc;
                } else { // delete
                    if ((ops[i].c[1] == 'R' && x == r) ||
                        (ops[i].c[1] == 'C' && x == c))
                        return false;
                    if (ops[i].c[1] == 'R' && x < r)
                        --dr;
                    if (ops[i].c[1] == 'C' && x < c)
                        --dc;
                }
            }
            r += dr, c += dc;
        }
    }
    return true;
}

int main() {
    int cases = 0;
    while (scanf("%d%d%d", &row, &col, &n) == 3 && row && col) {
        for (int i = 0; i < n; ++i) {
            scanf("%s", ops[i].c);
            if (ops[i].c[0] == 'E') { // exchange
                scanf("%d%d%d%d", &ops[i].un.r1, &ops[i].un.c1, &ops[i].un.r2,
                      &ops[i].un.c2);
            } else {
                scanf("%d", &ops[i].un.A);
                for (int j = 0; j < ops[i].un.A; ++j)
                    scanf("%d", &ops[i].un.x[j]);
            }
        }
        if (cases > 0)
            puts("");
        printf("Spreadsheet #%d\n", ++cases);

        int query;
        scanf("%d", &query);
        while (query-- > 0) {
            int r, c;
            scanf("%d%d", &r, &c);
            printf("Cell data in (%d,%d) ", r, c);
            if (!doit(r, c))
                puts("GONE");
            else
                printf("moved to (%d,%d)\n", r, c);
        }
    }
    return 0;
}
