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
#include <stdint.h>

/*
 * C(N - 1 + T - N * P, N - 1)
 */

#define rep(i, s, e) for (int i = s; i <= e; ++i)
#define pre(i, s, e) for (int i = s; i >= e; --i)

#define pi (acos(-1.0))
#define eps (1e-9)
#define inf 0x7f7f7f7f

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int64_t f[71] = {1};

    int K;
    int N, T, P;
    cin >> K;
    while (K-- > 0) {
        cin >> N >> T >> P;
        for (int i = 1; i <= T - N * P; ++i)
            f[i] = f[i - 1] * (N - 1 + i) / i;
        cout << f[T - N * P] << endl;
    }

    return 0;
}
