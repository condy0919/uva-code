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

struct foo {
    int priority;
    bool focus;

    foo(bool f = false) : priority(1), focus(f) {}
    bool operator<(const foo& rhs) const {
        return priority < rhs.priority;
    }
};

int main() {
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while (T-- > 0) {
        int n, pos;
        cin >> n >> pos;
        vector<foo> vec(n);
        for (int i = 0; i < n; ++i)
            cin >> vec[i].priority;
        vec[pos].focus = true;
        int cnt = 0;
        while (true) {
            auto iter = max_element(vec.begin(), vec.end());
            rotate(vec.begin(), iter, vec.end());
            ++cnt;
            if (vec.front().focus) {
                cout << cnt << '\n';
                break;
            }
            vec.erase(vec.begin());
        }
    }

    return 0;
}
