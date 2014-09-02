#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
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

/*
 * 一棵树上两个点的最远距离。
 * 一开始还以为分类错了，原来真是dfs..
 * 详细分析见: http://blog.chinaunix.net/uid-20128696-id-3157545.html
 */

using namespace std;

struct node {
    int rhs, dis;
};

vector<node> tree[10001];

int dfs(int prev, int cur, int& _max) {
    vector<int> m;
    for (const auto& i : tree[cur]) {
        if (prev == i.rhs)
            continue;
        m.push_back(dfs(cur, i.rhs, _max) + i.dis);
    }
    sort(m.rbegin(), m.rend()); // sort by descending
    _max = std::max(_max, accumulate(m.begin(), m.begin() + min(static_cast<size_t>(2), m.size()), 0));
    return accumulate(m.begin(), m.begin() + min(static_cast<size_t>(1), m.size()), 0);
}

int main() {
    ios::sync_with_stdio(false);

    string line;
    int a, b, d;
    while (!cin.eof()) {
        for (auto& i : tree)
            i.clear();
        getline(cin, line);
        while (!line.empty() && !cin.eof()) {
            istringstream iss(line);
            iss >> a >> b >> d;
            tree[a].push_back({b, d});
            tree[b].push_back({a, d});
            getline(cin, line);
        }

        int _max = 0;
        dfs(0, 1, _max);
        cout << _max << endl;
    }

    return 0;
}
