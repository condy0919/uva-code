#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cstring>

/*
 * 按照右端点坐标进行排序，这样才能尽可能地让更多的线段共享已选中的点.
 */

using namespace std;

int cases;
int K, N;
bool vis[20001];

struct jogger_t {
    int l, r;
} jogger[1001];

bool cmp(const jogger_t& a, const jogger_t& b) {
    return a.r < b.r;
}

int main() {
    cin >> cases;
    int l, r;

    while (cases-- > 0) {
        cin >> K >> N;
        for (int i = 0; i < N; ++i) {
            cin >> l >> r;
            if (l > r)
                swap(l, r);
            jogger[i].l = l + 10000;
            jogger[i].r = r + 10000;
        }
        sort(jogger, jogger + N, cmp);
        memset(vis, false, sizeof(vis));
        for (int i = 0; i < N; ++i) {
            int t = K - accumulate(vis + jogger[i].l, vis + jogger[i].r + 1, 0);
            for (int j = jogger[i].r; j >= jogger[i].l && t > 0; --j)
                if (!vis[j]) {
                    vis[j] = true;
                    --t;
                }
        }
        vector<int> ans;
        for (int i = 0; i < 20001; ++i)
            if (vis[i])
                ans.push_back(i - 10000);
        cout << ans.size() << endl;
        for_each(ans.begin(), ans.end(), [](int x){cout << x << endl;});
        if (cases)
            cout << endl;
    }
    return 0;
}
