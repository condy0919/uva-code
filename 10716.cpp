#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>

/*
 * 模拟一下贪心的策略.
 */

using namespace std;

int cnt[26];

bool poss(const string& s)
{
    memset(cnt, 0, sizeof(cnt));
    bool flag = false;
    for (int i = 0; i < s.length(); ++i)
        ++cnt[s[i] - 'a'];
    for (int i = 0; i < 26; ++i)
        if (cnt[i] & 1) {
            if (flag)
                return false;
            flag = true;
        }
    return true;
}

int calc(string s)
{
    int lo = 0, hi = s.length() - 1;
    int ret = 0;

    for (int lo = 0, hi = s.length() - 1; lo < hi; ++lo, --hi) {
        if (s[lo] == s[hi])
            continue;

        // let s[hi] equal to s[lo]
        int d1 = 0, d2 = 0;
        int i, j;
        for (i = hi; i > lo; --i, ++d1)
            if (s[lo] == s[i])
                break;

        // let s[lo] equal to s[hi]
        for (j = lo; j < hi; ++j, ++d2)
            if (s[hi] == s[j])
                break;

        if (d1 < d2) {
            ret += d1;
            for (int k = i; k < hi; ++k)
                swap(s[k], s[k + 1]);
        } else {
            ret += d2;
            for (int k = j; k > lo; --k)
                swap(s[k], s[k - 1]);
        }
    }
    return ret;
}

int main()
{
    int n;
    string s;
    cin >> n;

    while (n-- > 0) {
        cin >> s;
        if (!poss(s))
            cout << "Impossible\n";
        else
            cout << calc(s) << endl;
    }
    return 0;
}
