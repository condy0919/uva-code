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
 * -------------------- i -------
 *                      ^ 表示第i个topic.
 * num[i]表示在讲完第i个topic时总共用了多少个lecture.
 * 则
 * ----------- j ------ i -------
 *             ^        ^
 *             从[j, i]这时间长度如果在L范围内，
 *             则以这段新开一个lecture, 总的lecture 就是num[j-1] + 1，以此来更新。
 */

#define rep(i, s, e) for (int i = s; i <= e; ++i)
#define pre(i, s, e) for (int i = s; i >= e; --i)

#define pi (acos(-1.0))
#define eps (1e-9)
#define inf 0x7f7f7f7f

using namespace std;

int N;
int L, C;
int t[1001];
int num[1001], di[1001];
int s[1001];

#define S(i, j) (s[j] - s[i - 1])

int DI(int x) {
    if (x == 0)
        return 0;
    if (x >= 1 && x <= 10)
        return -C;
    return (x - 10) * (x - 10);
}

int main() {
    ios::sync_with_stdio(false);

    int cases = 0;
    bool first = true;
    while (cin >> N, N) {
        cin >> L >> C;
        rep(i, 1, N)
            cin >> t[i];
        partial_sum(t + 1, t + N + 1, s + 1);

        rep(i, 1, N) {
            num[i] = di[i] = inf;
            rep(j, 1, i) {
                if (S(j, i) > L)
                    continue;
                if (num[i] > num[j - 1] + 1) {
                    num[i] = num[j - 1] + 1;
                    di[i] = di[j - 1] + DI(L - S(j, i));
                } else if (num[i] == num[j - 1] + 1) {
                    di[i] = min(di[i], di[j - 1] + DI(L - S(j, i)));
                }
            }
        }
        if (first)
            first = false;
        else
            cout << endl;
        cout << "Case " << ++cases << ":" << endl;
        cout << "Minimum number of lectures: " << num[N] << endl;
        cout << "Total dissatisfaction index: " << di[N] << endl;
    }

    return 0;
}
