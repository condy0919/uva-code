#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

/*
 * 就是求最小覆盖的个数.
 */

using namespace std;

struct line_t {
    double l, r;

    line_t(double _l = 0.0, double _r = 0.0):l(_l), r(_r) {}
};

bool cmp_r(const line_t& a, const line_t& b) {
    return a.r < b.r;
}

int d;

double l(int x, int y) {
    return x - sqrt(d*d - y*y);
}
double r(int x, int y) {
    return x + sqrt(d*d - y*y);
}

int solve(vector<line_t>& vec) {
    sort(vec.begin(), vec.end(), cmp_r);
    int i, j, cnt = 0;
    for (i = 0; i < vec.size();  ++cnt) {
        for (j = i + 1; j < vec.size() && vec[i].r >= vec[j].l; ++j)
            ;
        i = j;
    }
    return cnt;
}

int main() {
    int cases = 0;
    int n;
    int x, y;

    while (cin >> n >> d, n || d) {
        vector<line_t> vec;
        bool unsolvable = false;
        for (int i = 0; i < n; ++i) {
            cin >> x >> y;
            if (y > d)
                unsolvable = true;
            vec.push_back(line_t(l(x, y), r(x, y)));
        }
        cout << "Case " << ++cases << ": " << (unsolvable ? -1 : solve(vec)) << endl;
    }
    return 0;
}
