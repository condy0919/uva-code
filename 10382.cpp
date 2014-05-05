#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

/*
 * 一开始错误地用`pos - radius'的排序，结果错了。。。
 */

using namespace std;

#define SQR(x) ((x)*(x))

struct sprinkler {
    double left, right;

    sprinkler(double _l = 0, double _r = 0):left(_l), right(_r) {}

    bool operator<(const sprinkler& rh) const {
        return left < rh.left;
    }
};

int n, l, w;
vector<sprinkler> a;

int solve()
{
    double left = 0, right = l;
    int cnt = 0;
    int i = 0;

    while (left < right) {
        bool found = false;
        double rightest = left;
        for (; i < a.size() && a[i].left <= left; ++i)
            if (a[i].right > rightest) {
                found = true;
                rightest = a[i].right;
            }
        if (!found)
            return -1;
        left = rightest;
        ++cnt;
    }
    return cnt;
}

int main()
{
    double pos, r, d;
    while (cin >> n >> l >> w) {
        a.clear();
        for (int i = 0; i < n; ++i) {
            cin >> pos >> r;
            if (r <= w/2.0)
                continue;
            d = sqrt(SQR(r) - SQR(w/2.0));
            if (pos - d >= l || pos + d <= 0)
                continue;
            a.push_back(sprinkler(pos - d, pos + d));
        }
        sort(a.begin(), a.end());
        cout << solve() << endl;
    }
    return 0;
}
