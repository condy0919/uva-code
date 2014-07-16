#include <iostream>
#include <algorithm>

#define inf 10000

using namespace std;

/*
 * 由于这题中向量(a, b) {a,b都为正数}. 则此dp是有方向的，则可以从左下角推到右上角。
 * 动态方程为: d[x][y] = min{d[x - Xi][y - Yi] + 1} for i in length(e-coins).
 */

struct point {
    int x, y;
    friend istream& operator>>(istream& in, point& p) {
        return in >> p.x >> p.y;
    }
} pts[41];

int T;
int m, r;
int d[301][301];

int main() {
    ios::sync_with_stdio(false);

    cin >> T;
    while (T-- > 0) {
        cin >> m >> r;
        for (int i = 0; i < m; ++i)
            cin >> pts[i];
        for (int i = 0; i < 301; ++i)
            fill(d[i], d[i] + 301, inf);
        d[0][0] = 0;
        for (int x = 0; x <= r; ++x) {
            for (int y = 0; y <= r; ++y) {
                if (x * x + y * y > r * r)
                    continue;
                for (int i = 0; i < m; ++i)
                    if (x >= pts[i].x && y >= pts[i].y)
                        d[x][y] = min(d[x - pts[i].x][y - pts[i].y] + 1, d[x][y]);
            }
        }
        bool have = false;
        int ans = inf;
        for (int x = 0; x <= r; ++x) {
            for (int y = 0; y <= r; ++y) {
                if (x * x + y * y > r * r)
                    continue;
                if (x * x + y * y == r * r && ans > d[x][y]) {
                    have = true;
                    ans = d[x][y];
                }
            }
        }
        if (have)
            cout << ans << endl;
        else
            cout << "not possible" << endl;
    }
    return 0;
}
