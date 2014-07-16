#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int dp[25001];

string tras(const string& s, char ch, int pos, int type) {
    if (type == 0)
        return std::move(string(s).replace(pos, 1, 1, ch));
    if (type == 1)
        return std::move(string(s).insert(pos, 1, ch));
    string ret(s);
    ret.erase(ret.begin() + pos);
    return std::move(ret);
}

int main() {
    ios::sync_with_stdio(false);
    vector<string> svec;
    string s;

    while (cin >> s)
        svec.push_back(s);

    int ans = 0;
    for (int i = 0; i < svec.size(); ++i) {
        dp[i] = 1;
        
        // replace | insert
        for (int t = 0; t < 2; ++t)
            for (int j = 0; j < svec[i].length(); ++j)
                for (char c = 'a'; c <= 'z'; ++c) {
                    s = tras(svec[i], c, j, t);
                    if (svec[i] < s)
                        break;
                    int p = lower_bound(svec.begin(), svec.begin() + i, s) - svec.begin();
                    if (p < i && svec[p] == s)
                        dp[i] = max(dp[i], dp[p] + 1);
                }
        // delete.
        for (int j = 0; j < svec[i].length(); ++j) {
            s = tras(svec[i], 0, j, 2);
            int p = lower_bound(svec.begin(), svec.begin() + i, s) - svec.begin();
            if (p < i && svec[p] == s)
                dp[i] = max(dp[i], dp[p] + 1);
        }

        ans = max(ans, dp[i]);
    }
    cout << ans << endl;

    return 0;
}
