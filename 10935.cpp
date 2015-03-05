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

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    if (v.empty())
        return os;
    for (int i = 0; i < v.size() - 1; ++i)
        os << ' ' << v[i] << ',';
    return os << ' ' << v.back();
}

int main() {
    ios::sync_with_stdio(false);

    int n;
    while (cin >> n, n) {
        vector<int> v(n);
        vector<int> discards;
        iota(v.rbegin(), v.rend(), 1);
        while (v.size() > 1) {
            discards.push_back(v.back());
            v.pop_back();
            int t = v.back();
            v.pop_back();
            v.insert(v.begin(), t);
        }
        cout << "Discarded cards:" << discards << '\n';
        cout << "Remaining card: " << v.back() << '\n';
    }

    return 0;
}
