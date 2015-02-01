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
#include <sstream>

#define rep(i, s, e) for (int i = s; i <= e; ++i)
#define pre(i, s, e) for (int i = s; i >= e; --i)

#define pi (acos(-1.0))
#define eps (1e-9)
#define inf 0x7f7f7f7f

using namespace std;

int G[10000][10];
map<string, int> id_cache;
vector<string> string_cache;

int id(const string& s) {
    if (id_cache.count(s))
        return id_cache[s];
    string_cache.push_back(s);
    return id_cache[s] = string_cache.size() - 1;
}

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    while (cin >> n >> m) {
        id_cache.clear();
        string_cache.clear();

        cin.ignore();
        string line, s;
        for (int i = 0; i < n; ++i) {
            getline(cin, line);
            istringstream iss(line);
            for (int j = 0; j < m; ++j) {
                getline(iss, s, ',');
                G[i][j] = id(s);
            }
        }

        int c_1, c_2, r_1, r_2;
        bool yes = true;
        for (int c1 = 0; c1 < m && yes; ++c1) {
            for (int c2 = c1 + 1; c2 < m && yes; ++c2) {
                map<pair<int, int>, int> S;
                for (int i = 0; i < n && yes; ++i) {
                    pair<int, int> pr = {G[i][c1], G[i][c2]};
                    if (S.count(pr)) {
                        c_1 = c1 + 1;
                        c_2 = c2 + 1;
                        r_1 = S[pr] + 1;
                        r_2 = i + 1;
                        yes = false;
                        break;
                    } else {
                        S[pr] = i; // 手贱，这里写了1没看出来。
                    }
                }
            }
        }
        if (yes) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
            cout << r_1 << ' ' << r_2 << '\n';
            cout << c_1 << ' ' << c_2 << '\n';
        }
    }

    return 0;
}
