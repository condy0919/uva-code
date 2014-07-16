#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define N 1001

struct elem_t {
    int w, s;
    bool operator<(const elem_t& rhs) const {
        return w < rhs.w && s > rhs.s;
    }
} pool[N];

int n, d[N], _next[N];

int dp(int u) {
    if (d[u])
        return d[u];
    d[u] = 1;
    for (int i = 0; i < n; ++i)
        if (pool[u] < pool[i]) {
            int val = dp(i) + 1;
            if (val > d[u]) {
                d[u] = val;
                _next[u] = i;
            }
        }
    return d[u];
}

int main() {
    while (cin >> pool[n].w >> pool[n].s)
        ++n;

    fill(d, d + n, 0);
    fill(_next, _next + n, -1);
    for (int i = 0; i < n; ++i)
        if (!d[i])
            dp(i);
    vector<int> ans;
    for (int i = max_element(d, d + n) - d; i != -1; i = _next[i])
        ans.push_back(i + 1);
    cout << ans.size() << endl;
    for_each(ans.begin(), ans.end(), [](int x) {cout << x << endl;});

    return 0;
}
