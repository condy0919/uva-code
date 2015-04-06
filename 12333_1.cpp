/*
 * copy from http://blog.csdn.net/kun768/article/details/43535053
 */

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int id;
    Node *next[10];
    Node() {
        id = -1;
        for (int i = 0; i < 10; ++i) next[i] = NULL;
    }
};
char Fib[50], In[50];
int F[2][1024000];
Node *const root = new Node();

void add_node(char *str, int id) {
    Node *u = root;
    for (int i = 0, len = strlen(str); i < len && i <= 40; ++i) {
        int v = str[i] - '0';
        if (!u->next[v]) u->next[v] = new Node();
        u = u->next[v];
        if (u->id == -1) u->id = id;
    }
}
int query(char *str) {
    Node *u = root;
    for (size_t i = 0, len = strlen(str); i < len; ++i) {
        u = u->next[str[i] - '0'];
        if (!u) return -1;
    }
    return u->id;
}
void init() {
    memset(F, 0, sizeof(F));
    F[0][0] = F[1][0] = 1;
    int s = 0, e = 1;
    add_node((char *)"1", 0);
    add_node((char *)"1", 1);
    for (int i = 2; i < 100000; ++i) {
        int p = i % 2, q = (i + 1) % 2;
        for (int j = s; j < e; ++j)
            F[p][j] = F[p][j] + F[q][j];
        for (int j = s; j < e; ++j) {
            if (F[p][j] >= 10) {
                F[p][j] %= 10;
                F[p][j + 1] += 1;
            }
        }
        if (F[p][e]) ++e;
        if (e - s > 50) ++s;
        int r = e - 1, cnt = 0;
        memset(Fib, 0, sizeof(Fib));
        while (r >= 0 && cnt < 45) Fib[cnt++] = F[p][r--] + '0';
        add_node(Fib, i);
    }
}
int main() {
    ios::sync_with_stdio(false);
    init();
    int T;
    cin >> T;
    for (int i = 1; i <= T; ++i) {
        cin >> In;
        printf("Case #%d: %d\n", i, query(In));
    }
    return 0;
}
