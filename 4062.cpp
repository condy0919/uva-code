#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>
#include <cstdio>

/*
 * 虽然思路很清晰，但不明白它的cat函数作用是什么。
 */

using namespace std;

#define pi (acos(-1.0))
#define eps (1e-6)

struct point_t {
    double x, y;
    point_t(double _x = 0, double _y = 0):x(_x), y(_y) {}
    point_t rotate(double theta) {
        double _x = x * cos(theta) + y * sin(theta), _y = -x * sin(theta) + y * cos(theta);
        (x = _x), (y = _y);
        return *this;
    }
};

double e, k, theta;
int n;

bool cmp_x(const point_t& a, const point_t& b) {
    return a.x < b.x;
}

bool cmp_y(const point_t& a, const point_t& b) {
    return a.y < b.y;
}

double cat(const point_t& a, const point_t& b) {
    double x = fabs(a.x - b.x) / 2.0;
    double y = fabs(a.y - b.y) / 2.0;
    return x * x + y * y / k;
}

double solve(vector<point_t>& a) {
    double ret = numeric_limits<double>::max();
    bool (*pfunc[2])(const point_t&, const point_t&) = {cmp_x, cmp_y};

    for (int f = 0; f < 2; ++f) {
        sort(a.begin(), a.end(), pfunc[f]);
        for (int i = 1; i < a.size(); ++i) {
            double t = cat(a[i - 1], a[i]);
            ret = min(ret, t);
        }
    }
    return ret;
}

int main() {
    int cases = 0, n;
    while (cin >> n >> e >> theta, n && e && theta) {
        theta = theta * pi / 180.0;
        k = 1 - e * e;
        vector<point_t> a;
        double _x, _y;
        for (int i = 0; i < n; ++i) {
            cin >> _x >> _y;
            a.push_back(point_t(_x, _y).rotate(theta));
        }
        printf("Case %d:\n", ++cases);
        printf("%.6lf\n", pi * solve(a) * sqrt(k));
    }
    return 0;
}
