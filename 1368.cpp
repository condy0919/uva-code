#include <iostream>
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

int T;
int M, N;
char gs[51][1001];

int r(char ch) {
    switch (ch) {
    case 'A':
        return 0;
    case 'C':
        return 1;
    case 'G':
        return 2;
    case 'T':
        return 3;
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);

    cin >> T;
    while (T-- > 0) {
        cin >> M >> N;
        for (int i = 0; i < M; ++i)
            cin >> gs[i];
        int dif = 0;
        for (int j = 0; j < N; ++j) {
            int cnt[4] = {0};
            for (int i = 0; i < M; ++i)
                ++cnt[r(gs[i][j])];
            char c = *("ACGT" + (max_element(cnt, cnt + 4) - cnt));
            cout << c;
            dif += M - cnt[r(c)];
        }
        cout << endl << dif << endl;
    }


    return 0;
}
