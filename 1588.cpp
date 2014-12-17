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

    string a, b;
    while (cin >> a >> b) {
        int lena = a.length(), lenb = b.length();
        int ans = lena + lenb;
        for (int i = -lenb; i < lena; ++i) {
            bool flag = true;
            for (int j = 0; j < lenb && i + j < lena; ++j) {
                if (i + j < 0)
                    continue;
                if (a[i + j] - '0' + b[j] - '0' > 3) {
                    flag = false;
                    break;
                }
            }
            if (flag && i < 0)
                ans = min(ans, max(lena - i, lenb));
            else if (flag)
                ans = min(ans, max(lena, lenb + i));
        }
        cout << ans << endl;
    }

    return 0;
}
