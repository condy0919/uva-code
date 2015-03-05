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

int main() {
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while (T-- > 0) {
        int n;
        cin >> n;
        vector<pair<int, int> > pts(n);
        for (int i = 0; i < n; ++i)
            cin >> pts[i].first >> pts[i].second;

        sort(pts.begin(), pts.end());
        bool flag = true;
        int s = (n % 2 == 1) ? 2 * pts[n / 2].first : pts[n / 2].first + pts[n / 2 - 1].first;
        for (int i = 0; i < n; ++i) {
            pair<int, int> opposite(s - pts[i].first, pts[i].second);
            if (!binary_search(pts.begin(), pts.end(), opposite)) {
                flag = false;
                break;
            }
        }

        cout << (flag ? "YES\n" : "NO\n");
    }

    return 0;
}
