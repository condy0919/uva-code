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
 * 真是万万没有想到啊！剪枝剪了以后状态会少那么多。
 * 不知道是数据水，还是这种方法所隐藏剪掉的状态比较多？？
 * 具体分析见
 *      http://www.cnblogs.com/staginner/archive/2011/12/07/2279783.html
 *      http://blog.csdn.net/yan_____/article/details/8671147
 */

#define rep(i, s, e) for (int i = s; i <= e; ++i)
#define pre(i, s, e) for (int i = s; i >= e; --i)

#define pi (acos(-1.0))
#define eps (1e-9)
#define inf 0x7f7f7f7f

using namespace std;

int T;
int wine, N;
int low[101], high[101];
int f[450001];
bool vis[4501];

int main() {
    ios::sync_with_stdio(false);

    cin >> T;
    while (T-- > 0) {
        cin >> wine >> N;
        wine *= 1000;
        int k = inf;
        for (int i = 0; i < N; ++i) {
            cin >> low[i] >> high[i];
            k = min(k, low[i] * int(ceil(low[i] / (high[i] - low[i]))));
        }
        if (wine >= k) {
            cout << 0 << endl;
        } else {
            vector<int> bottles;
            memset(vis, 0, sizeof(vis));
            memset(f, 0, sizeof(f));
            for (int i = 0; i < N; ++i) {
                for (int j = low[i]; j <= high[i]; ++j) {
                    if (!vis[j]) {
                        vis[j] = true;
                        bottles.push_back(j);
                    }
                }
            }
            for (const auto& weight : bottles)
                for (int j = weight; j <= wine; ++j)
                    f[j] = max(f[j], f[j - weight] + weight);
            cout << wine - f[wine] << endl;
        }
        if (T)
            cout << endl;
    }

    return 0;
}
