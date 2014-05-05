#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

struct obj {
    int matched, unmatched;

    obj(int _m, int _u): matched(_m), unmatched(_u) {}
    bool operator > (const obj& rh) {
        if (matched > rh.matched)
            return true;
        if (matched < rh.matched)
            return false;
        return unmatched < rh.unmatched;
    }
};

struct cmpobj {
    string ori;

    cmpobj(const string& s) : ori(s) {}

    obj match(const string& rh) {
        int len = min(ori.length(), rh.length());
        int i;

        obj ret(0, 0);
        for (i = 0; i < len; ++i)
            if (ori[i] != rh[i])
                break;
        ret.matched = i;
        ret.unmatched = ori.length() + rh.length() - i - i;
        return ret;
    }
};

int N;
vector<string> a;

int sort(vector<string>& a)
{
    int s = 0;
    for (int i = 0; i < a.size() - 1; ++i) {
        cmpobj cmp(a[i]);
        int k = i + 1;
        for (int j = i + 1; j < a.size(); ++j)
            if (cmp.match(a[j]) > cmp.match(a[k]))
                k = j;
        swap(a[i + 1], a[k]);
        s += a[i + 1].length() - cmp.match(a[i + 1]).matched;
    }
    return s;
}

int main()
{
    int T;
    string s;
    cin >> T;
    while (T-- > 0) {
        cin >> N;
        a.clear();
        for (int i = 0; i < N; ++i) {
            cin >> s;
            a.push_back(s);
        }
        int ans = sort(a) + a[0].length();
        cout << ans << endl;
        for (int i = 0; i < a.size(); ++i)
            cout << a[i] << endl;
    }
    return 0;
}
