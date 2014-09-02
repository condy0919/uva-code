#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <functional>
#include <numeric>
#include <limits>
#include <cstring>

using namespace std;

/*
 * 难得的1A啊..QAQ~
 */

unsigned long long factorial(int n) {
    static unsigned long long f[16] = { 1 };
    if (!f[n])
        f[n] = factorial(n - 1) * n;
    return f[n];
}

unsigned long long perm(const map<char, int> &cnt) {
    unsigned long long s = factorial(
        accumulate(cnt.begin(), cnt.end(), 0,
                   [](unsigned long long init,
                      const pair<char, int> &p) { return init + p.second; }));
    for (const auto &p : cnt)
        if (p.second)
            s /= factorial(p.second);
    return s;
}

string solve(map<char, int> &cnt, unsigned long long exp) {
    if (cnt.empty())
        return "";

    string ret;
    for (auto iter = cnt.begin(); iter != cnt.end(); ++iter) {
        --iter->second;
        unsigned long long t = perm(cnt);
        if (exp <= t) {
            ret += iter->first;
            if (!iter->second)
                cnt.erase(iter);
            break;
        }
        ++iter->second;
        exp -= t;
    }
    return ret + solve(cnt, exp);
}

int main() {
    ios::sync_with_stdio(false);

    string line;
    unsigned long long exp;

    int T;
    cin >> T;
    for (int cases = 0; cases < T; ++cases) {
        cout << "Case " << cases + 1 << ": ";
        cin >> line >> exp;

        map<char, int> cnt;
        for (const auto &ch : line)
            ++cnt[ch];
        auto odd = [](const pair<char, int> &p) { return p.second % 2 == 1; };
        if (count_if(cnt.begin(), cnt.end(), odd) > 1) {
            cout << "XXX" << endl;
            continue;
        }

        auto iter = find_if(cnt.begin(), cnt.end(), odd);
        string special = "";
        if (iter != cnt.end()) {
            special += iter->first;
            --iter->second;
            if (!iter->second)
                cnt.erase(iter);
        }

        for (auto& p : cnt)
            p.second /= 2;

        if (exp > perm(cnt)) {
            cout << "XXX" << endl;
            continue;
        }

        string s = solve(cnt, exp);
        string r(s.rbegin(), s.rend());
        cout << s + special + r << endl;
    }

    return 0;
}
