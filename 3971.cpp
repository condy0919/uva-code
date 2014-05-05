#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
using namespace std;

/*
 * 这题做得真辛苦啊。看网上各种解答，始终不明白为什么要把二分写成那种形式。
 * 后来记录了一下前一个可能的答案，就过了。(。・_・。)
 * 然后自己又测试了一下，发现只能保证所花钱数在budget内，然后才考虑quality。
 * 或者是我又漏掉了哪些情况没有考虑到。
 */

struct elem_t {
    int price, quality;

    elem_t(int _p = 0.0, int _q = 0.0):price(_p), quality(_q) {}

    bool operator<(const elem_t& rh) const {
        return price < rh.price;
    }
};

bool P(map< string, vector<elem_t> >& S, int guess, int budget) {
    int cost = 0;
    for (map< string, vector<elem_t> >::iterator iter = S.begin(); iter != S.end(); ++iter) {
        vector<elem_t>& vec = iter->second;
        int i;
        for (i = 0; i < vec.size(); ++i)
            if (vec[i].quality >= guess)
                break;
        if (i == vec.size())
            return false;
        cost += vec[i].price;
    }
    return cost <= budget;
}

int main() {
    int T, n, b;

    string type, name;
    int price, quality;

    cin >> T;
    while (T-- > 0) {
        cin >> n >> b;
        map< string, vector<elem_t> > S;
        int lo = 1000000000, hi = 0, mid;
        for (int i = 0; i < n; ++i) {
            cin >> type >> name >> price >> quality;
            S[type].push_back(elem_t(price, quality));
            lo = min(lo, quality);
            hi = max(hi, quality);
        }

        for (map< string, vector<elem_t> >::iterator iter = S.begin(); iter != S.end(); ++iter)
            sort(iter->second.begin(), iter->second.end());
        int ans;
        while (lo <= hi) {
            mid = (lo + hi) / 2;
            if (P(S, mid, b)) {
                lo = mid + 1;
                ans = mid;
            } else {
                hi = mid - 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
