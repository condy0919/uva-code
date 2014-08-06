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

/*
 * 先求得最大安全值，然后用这个最大安全值来解决最小花费。
 * ^ 这是网上大多数的解法，但还是不理解啊。
 */

#define rep(i, s, e) for (int i = s; i <= e; ++i)
#define pre(i, s, e) for (int i = s; i >= e; --i)

#define pi (acos(-1.0))
#define eps (1e-9)
#define inf 0x7f7f7f7f

using namespace std;

int N, M;
int P[31];
int safety[31][101], cost[31][101];

int main() {
    ios::sync_with_stdio(false);

    while (cin >> N >> M, N || M) {
        memset(safety, 0, sizeof(safety));
        for (int i = 0; i < 31; ++i)
            safety[i][0] = inf;

        rep(i, 1, M)
            cin >> P[i];

        rep(m, 1, M) {
            rep(n, 1, N) {
                safety[m][n] = safety[m - 1][n];
                rep(x, 1, n) {
                    safety[m][n] = max(safety[m][n], min(safety[m - 1][n - x], P[m] / x));
                }
            }
        }

        int lim = safety[M][N];
        memset(cost, 0x3f, sizeof(cost));
        rep(m, 1, M) {
            cost[m - 1][0] = 0;
            rep(n, 1, N) {
                cost[m][n] = cost[m - 1][n];
                rep(x, 1, n) {
                    if (P[m] / x >= lim)
                        cost[m][n] = min(cost[m][n], cost[m - 1][n - x] + P[m]);
                }
            }
        }

        cout << lim << " " << (lim ? cost[M][N] : 0) << endl;
    }

    return 0;
}
