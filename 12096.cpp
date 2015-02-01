#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <stack>
#include <vector>

using namespace std;

map<set<int>, int> id_cache;
vector<set<int>> set_cache;

int id(const set<int>& x) {
    if (id_cache.count(x)) return id_cache[x];
    set_cache.push_back(x);
    return id_cache[x] = set_cache.size() - 1;
}

int main() {
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while (T-- > 0) {
        stack<int> s;
        int n;
        cin >> n;
        while (n-- > 0) {
            string op;
            cin >> op;
            if (op[0] == 'P') {
                s.push(id(set<int>()));
            } else if (op[0] == 'D') {
                s.push(s.top());
            } else {
                set<int> x1 = set_cache[s.top()];
                s.pop();
                set<int> x2 = set_cache[s.top()];
                s.pop();
                set<int> x;

#define ALL(x) x.begin(), x.end()
#define INS(x) inserter(x, x.begin())
                if (op[0] == 'U')
                    set_union(ALL(x1), ALL(x2), INS(x));
                else if (op[0] == 'I')
                    set_intersection(ALL(x1), ALL(x2), INS(x));
                else if (op[0] == 'A') {
                    x = x2;
                    x.insert(id(x1));
                }
                s.push(id(x));
            }
            cout << set_cache[s.top()].size() << endl;
        }
        cout << "***\n";
    }
    return 0;
}
