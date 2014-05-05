#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstdio>
using namespace std;
#define dis(a,b) (sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2)))
struct point {
    double x, y;
};
bool cmp_x(const point& lh, const point& rh) {
    return lh.x < rh.x;
}
bool cmp_y(const point& lh, const point& rh) {
    return lh.y < rh.y;
}

double solve(const vector<point>& a, int beg, int end) {
    if (beg + 1 == end)
        return 20000.0;
    if (beg + 2 == end)
        return dis(a[beg], a[end - 1]);

    int mid = (beg + end) / 2;
    double d = min(solve(a, beg, mid), solve(a, mid, end));

    vector<point> region;
    for (int i = beg; i < end; ++i)
        if (fabs(a[i].x - a[mid].x) <= d)
            region.push_back(a[i]);
    sort(region.begin(), region.end(), cmp_y);
    for (int i = 0; i < region.size() - 1; ++i)
        for (int j = i + 1; j < region.size() && j < i + 7; ++j)
            d = min(d, dis(region[i], region[j]));
    return d;
}

int main() {
    int n;
    double x, y;
    while (cin >> n, n) {
        vector<point> a;
        for (int i = 0; i < n; ++i) {
            cin >> x >> y;
            a.push_back(point{x, y});
        }
        sort(a.begin(), a.end(), cmp_x);
        double ans = solve(a, 0, a.size());
        if (ans < 10000.0)
            printf("%.4lf\n", ans);
        else
            puts("INFINITY");
    }
    return 0;
}
