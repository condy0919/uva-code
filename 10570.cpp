#include <iostream>
#include <algorithm>

#define inf 0x7f7f7f7f

using namespace std;

int N;
int a[500];
int p[500], pos[500];

int next(int x) {
    return x == N - 1 ? 0 : x + 1;
}

int prev(int x) {
    return x == 0 ? N - 1 : x - 1;
}

// 又忘了修正pos对应的值了..QAQ
// 测试数据：http://online-judge.uva.es/board/viewtopic.php?f=25&t=4183
int solve() {
    /*
     * idx 0 1 2
     * val 2 0 1
     *
     * wanted ->
     *     0 1 2
     */
    int ret = 0;
    for (int i = 0; i < N; ++i) {
        if (p[i] == i)
            continue;
        p[pos[i]] = p[i];
        pos[p[i]] = pos[i];
        ++ret;
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);

    while (cin >> N, N) {
        for (int i = 0; i < N; ++i) {
            cin >> a[i];
            --a[i];
        }
        int ans = inf;
        for (int i = 0; i < N; ++i) {
            for (int j = 0, t = i; j < N; ++j, t = next(t)) {
                p[j] = a[t];
                pos[a[t]] = j;
            }
            ans = min(ans, solve());
        }
        for (int i = 0; i < N; ++i) {
            for (int j = 0, t = i; j < N; ++j, t = prev(t)) {
                p[j] = a[t];
                pos[a[t]] = j;
            }
            ans = min(ans, solve());
        }
        cout << ans << endl;
    }

    return 0;
}
