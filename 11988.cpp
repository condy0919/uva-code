#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <set>
#include <list>
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

    string s;
    while (cin >> s) {
        list<char> lst;
        list<char>::iterator pos = lst.begin();
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == '[') {
                pos = lst.begin();
            } else if (s[i] == ']') {
                pos = lst.end();
            } else {
                lst.insert(pos, s[i]);
            }
        }
        string ans(lst.begin(), lst.end());
        cout << ans << '\n';
    }

    return 0;
}
