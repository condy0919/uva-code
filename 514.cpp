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

static const char* choice[] = {"No", "Yes"};

bool check(queue<int>& perm) {
    stack<int> S;
    int total = perm.size(), cur = 0;

    while (!perm.empty()) {
        while (S.empty() || S.top() != perm.front()) {
            if (cur == total)
                return false;
            S.push(++cur);
        }
        perm.pop();
        S.pop();
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);

    // n <= 1000
    int n;
    while (cin >> n, n) {
        queue<int> perm;
        int x;
        while (cin >> x, x) {
            while (!perm.empty())
                perm.pop();
            perm.push(x);
            for (int i = 1; i < n; ++i) {
                cin >> x;
                perm.push(x);
            }
            cout << choice[check(perm)] << '\n';
        }
        cout << '\n';
    }

    return 0;
}
