#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <algorithm>

/*
 * 照着example抄了一遍，只不过把警告给消掉了.
 */

using namespace std;

#define MAXN 144
#define CUT 70

struct player_t {
    char name[25];
    int amateur;
    int sc[4];
    int sc36, sc72, dq;
    int rnds;
} player[MAXN];

int n;
double purse, p[CUT];

bool cmp1(const player_t& p1, const player_t& p2) {
    if (p1.sc36 < 0 && p2.sc36 < 0) return false;
    if (p1.sc36 < 0) return false;
    if (p2.sc36 < 0) return true;
    return p1.sc36 < p2.sc36;
}

bool cmp2(const player_t& p1, const player_t& p2) {
    if (p1.dq && p2.dq) {
        if (p1.rnds != p2.rnds) return p2.rnds < p1.rnds;
        if (p1.sc72 != p2.sc72) return p1.sc72 < p2.sc72;
        return strcmp(p1.name, p2.name) < 0;
    }
    if (p1.dq) return false;
    if (p2.dq) return true;
    if (p1.sc72 != p2.sc72) return p1.sc72 < p2.sc72;
    return strcmp(p1.name, p2.name) < 0;
}

void print_result() {
    printf("Player Name          Place     RD1  RD2");
    printf("  RD3  RD4  TOTAL     Money Won\n");
    printf("---------------------------------------");
    printf("--------------------------------\n");

    int i = 0, pos = 0;
    while (i < n) {
        if (player[i].dq) {
            printf("%s           ", player[i].name);
            for (int j = 0; j < player[i].rnds; ++j)
                printf("%-5d", player[i].sc[j]);
            for (int j = 0; j < 4 - player[i].rnds; ++j) printf("     ");
            puts("DQ");
            ++i;
            continue;
        }

        int j = i;
        int m = 0;
        bool have_money = false;
        double total = 0.0;
        while (j < n && player[i].sc72 == player[j].sc72) {
            if (!player[j].amateur) {
                ++m;
                if (pos < CUT) {
                    have_money = true;
                    total += p[pos++];
                }
            }
            ++j;
        }

        int rank = i + 1;
        double amount = purse * total / m;
        while (i < j) {
            printf("%s ", player[i].name);
            char t[5];
            sprintf(t, "%d%c", rank,
                    m > 1 && have_money && !player[i].amateur ? 'T' : ' ');
            printf("%-10s", t);
            for (int k = 0; k < 4; ++k) printf("%-5d", player[i].sc[k]);

            // with prize
            if (!player[i].amateur && have_money) {
                printf("%-10d", player[i].sc72);
                printf("$%9.2lf\n", amount / 100.0);
            } else {
                printf("%d\n", player[i].sc72);
            }
            ++i;
        }
    }
}

template<size_t N>
void my_gets(char (&s)[N]) {
    fgets(s, N, stdin);
    s[strlen(s) - 1] = '\0';
}

int main() {
    int T;
    char s[40];


    my_gets(s);
    sscanf(s, "%d", &T);
    while (T-- > 0) {
        my_gets(s);

        my_gets(s);
        sscanf(s, "%lf", &purse);
        for (int i = 0; i < CUT; ++i) {
            my_gets(s);
            sscanf(s, "%lf", &p[i]);
        }

        // players
        my_gets(s);
        sscanf(s, "%d", &n);
        for (int k = 0; k < n; ++k) {
            my_gets(s);

            strncpy(player[k].name, s, 20);
            player[k].name[20] = '\0';
            player[k].amateur = 0;
            if (strchr(player[k].name, '*')) player[k].amateur = 1;

            // score
            player[k].sc36 = player[k].sc72 = player[k].dq = 0;
            memset(player[k].sc, -1, sizeof(player[k].sc));
            for (int i = 0; i < 4; ++i) {
                char t[5];
                for (int j = 0; j < 3; ++j) t[j] = s[20 + i * 3 + j];
                t[3] = '\0';

                // parse
                if (!sscanf(t, "%d", &player[k].sc[i])) {
                    // DQ
                    player[k].rnds = i;
                    player[k].dq = 1;
                    if (i < 2) player[k].sc36 = -1;
                    break;
                } else {
                    player[k].sc72 += player[k].sc[i];
                    if (i < 2) player[k].sc36 += player[k].sc[i];
                }
            }
        }

        sort(player, player + n, cmp1);
        for (int i = CUT - 1; i < n; ++i) {
            if (i == n - 1 || player[i].sc36 != player[i + 1].sc36) {
                n = i + 1;
                break;
            }
        }
        sort(player, player + n, cmp2);
        print_result();
        if (T) puts("");
    }

    return 0;
}
