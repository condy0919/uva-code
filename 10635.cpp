#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/*
 * 一开始以为是普通的lcs，直接O(N^2)写了，结果本地测试直接无法编译。后来优化空间后，
 * 果断TLE呀。p*q ~ 250^4 ~ 48s耗时。
 * http://www.cnblogs.com/staginner/archive/2011/12/04/2275571.html
 * ^ 看这里了解到可以将lcs转化为lis如果某个串里面的item不一样的话。
 * ***** 转换的思想很重要呀！！ *****
 */

int T;
int n, p, q;
int idx[250 * 250 + 1];
int t;

int main() {
    ios::sync_with_stdio(false);

    cin >> T;
    for (int cases = 1; cases <= T; ++cases) {
        cin >> n >> p >> q;
        fill(idx, idx + 250 * 250 + 1, -1);
        for (int i = 0; i <= p; ++i) {
            cin >> t;
            idx[t] = i;
        }
        vector<int> ans;
        for (int i = 0; i <= q; ++i) {
            cin >> t;
            t = idx[t];
            // not exists.
            if (t == -1)
                continue;
            vector<int>::iterator it = lower_bound(ans.begin(), ans.end(), t);
            if (it == ans.end())
                ans.push_back(t);
            else if (t < *it)
                *it = t;
        }
        cout << "Case " << cases << ": " << ans.size() << endl;
    }
    return 0;
}
