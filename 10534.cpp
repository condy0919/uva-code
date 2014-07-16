#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

/*
 * 正方向找lis，反方向找lis，后取其较短序列 × 2 - 1 即可。
 */

int a[10000], n;
int l[10000], r[10000];
vector<int> vec;

int main() {
    ios_base::sync_with_stdio(false);
    while (cin >> n) {
        for (int i = 0; i < n; ++i)
            cin >> a[i];
        memset(l, 0, sizeof(l));
        memset(r, 0, sizeof(r));

        vec.clear();
        for (int i = 0; i < n; ++i) {
            auto j = lower_bound(vec.begin(), vec.end(), a[i]);
            if (j == vec.end()) {
                vec.push_back(a[i]);
                l[i] = vec.size();
            } else {
                *j = a[i];
                l[i] = j - vec.begin() + 1;
            }
        }
        vec.clear();
        for (int i = n - 1; i >= 0; --i) {
            auto j = lower_bound(vec.begin(), vec.end(), a[i]);
            if (j == vec.end()) {
                vec.push_back(a[i]);
                r[i] = vec.size();
            } else {
                *j = a[i];
                r[i] = j - vec.begin() + 1;
            }
        }
        int ans = 1;
        for (int i = 0; i < n; ++i)
                ans = max(ans, min(l[i], r[i]) * 2 - 1);
        cout << ans << endl;
    }
    return 0;
}
