#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <functional>

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int T, n;
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        set<vector<int>> S;
        vector<int> v(n);
        for (int i = 0; i < n; ++i)
            cin >> v[i];

        bool loop;
        while (true) {
            // if current state is found in S, loop occurs, then break.
            // if current state is all zeros, then break.
            if (all_of(v.begin(), v.end(), bind1st(equal_to<int>(), 0))) {
                loop = false;
                break;
            } else if (S.count(v)) {
                loop = true;
                break;
            }
            S.insert(v);
            int fst = v.front();
            for (int i = 0; i < n - 1; ++i)
                v[i] = abs(v[i + 1] - v[i]);
            v[n - 1] = abs(v[n - 1] - fst);
        }
        cout << (loop ? "LOOP\n" : "ZERO\n");
    }

    return 0;
}
