#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <bitset>
#include <utility>
#include <functional>
#include <numeric>
#include <limits>
#include <cmath>
#include <cctype>
#include <cstring>

#define rep(i, s, e) for (int i = s; i <= e; ++i)
#define pre(i, s, e) for (int i = s; i >= e; --i)

#define pi (acos(-1.0))
#define eps (1e-9)
#define inf 0x7f7f7f7f

using namespace std;

int r, c;
char G[11][11];
int S[11][11];

// get the white sequence
void init() {
    memset(S, 0, sizeof(S));
    int k = 0;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (G[i][j] == '*')
                continue;
            if (i - 1 < 0 || G[i - 1][j] == '*' || j - 1 < 0 ||
                G[i][j - 1] == '*')
                S[i][j] = ++k;
        }
    }
}

void across() {
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c;) {
            if (S[i][j] == 0) {
                ++j;
                continue;
            }
            printf("%3d.", S[i][j]);
            int k;
            for (k = j; k < c && G[i][k] != '*'; ++k)
                putchar(G[i][k]);
            puts("");
            j = k;
        }
    }
}

void down() {
    char buf[34] = {0};
    vector< pair<int, string> > out;
    for (int j = 0; j < c; ++j) {
        for (int i = 0; i < r;) {
            if (S[i][j] == 0) {
                ++i;
                continue;
            }

            pair<int, string> pr;
            pr.first = S[i][j];
            int k;
            for (k = i; k < r && G[k][j] != '*'; ++k)
                sprintf(buf + k - i, "%c", G[k][j]);
            i = k;
            pr.second = buf;
            out.push_back(pr);
        }
    }
    sort(out.begin(), out.end());
    for (int i = 0; i < out.size(); ++i)
        printf("%3d.%s\n", out[i].first, out[i].second.c_str());
}

int main() {
    int cases = 1;
    bool first = true;
    while (scanf("%d", &r), r != 0 && scanf("%d", &c) == 1) {
        if (first)
            first = false;
        else
            puts("");
        for (int i = 0; i < r; ++i)
            scanf("%s", G[i]);
        printf("puzzle #%d:\n", cases++);
        init();
        puts("Across");
        across();
        puts("Down");
        down();
    }

    return 0;
}
