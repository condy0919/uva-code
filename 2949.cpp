#include <iostream>
#include <algorithm>
#include <vector>

/*
 * 好坑的题，题目意思都不理解.QAQ
 */

using namespace std;

int n;
bool vis[32];
vector<int> solution;
int top;

bool P(int guess)
{
    vector<int> ans;
    for (int i = guess / 20 + 2; i <= top; ++i) {
        if (!vis[i])
            continue;
        int t = (i - 1) * 4 + ans.size() * 10;
        if (t > guess)
            return false;
        t = (guess - 10 * ans.size() + 20 * i + 4) / 24;
        i = (guess - 10 * ans.size() + 16 * t + 4) / 20;
        ans.push_back(t);
    }
    solution = ans;
    return true;
}

int main()
{
    int t;
    while (cin >> n, n > 0) {
        fill(vis, vis + 32, false);
        top = 0;
        for (int i = 0; i < n; ++i) {
            cin >> t;
            vis[t] = true;
            top = max(top, t);
        }

        int lo = 0, hi = 14 * (top - 1), mid;
        int ans;
        while (lo <= hi) {
            mid = (lo + hi) / 2;
            if (P(mid))
                (hi = mid - 1), (ans = mid);
            else
                lo = mid + 1;
        }
        cout << ans << endl << solution.size();
        for (int i = 0; i < solution.size(); ++i)
            cout << " " << solution[i];
        cout << endl;
    }
    return 0;
}
