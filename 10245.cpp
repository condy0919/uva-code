#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

struct point {
    double x, y;
    point(double _x = 0, double _y = 0):x(_x), y(_y) {}
    double dis(const point& rh) const {
        return sqrt(pow(x - rh.x, 2) + pow(y - rh.y, 2));
    }
};

bool cmp_x(const point& lh, const point& rh) {
    return lh.x < rh.x;
}

bool cmp_y(const point& lh, const point& rh) {
    return lh.y < rh.y;
}

double solve(const vector<point>& a, int l, int r)
{
    if (l == r)
        return 20000.0;
    if (l + 1 == r)
        return a[l].dis(a[r]);

    int mid = (l + r) / 2;
    double d = min(solve(a, l, mid), solve(a, mid + 1, r));

    vector<point> region;
    for (int i = l; i <= r; ++i)
        if (fabs(a[i].x - a[mid].x) <= d)
            region.push_back(a[i]);
    sort(region.begin(), region.end(), cmp_y);
    for (int i = 0; i < region.size(); ++i)
        for (int j = i + 1; j < region.size() && j < i + 7; ++j)
            d = min(d, region[i].dis(region[j]));
    return d;
}

int main()
{
    int n;
    double x, y;

    while (cin >> n, n) {
        vector<point> a;
        for (int i = 0; i < n; ++i) {
            cin >> x >> y;
            a.push_back(point(x, y));
        }
        sort(a.begin(), a.end(), cmp_x);
        double ans = solve(a, 0, a.size() - 1);
        if (ans < 10000.0)
            printf("%.4lf\n", ans);
        else
            puts("INFINITY");
    }
    return 0;
}
