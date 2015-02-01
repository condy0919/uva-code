#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct building {
    int id;
    double x, y;
    double w, h;
    bool operator<(const building& rhs) const {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
};

bool cover(const building& b, double x) { return x >= b.x && x <= b.x + b.w; }

bool visible(const building& b, double x, const vector<building>& bs) {
    if (!cover(b, x)) return false;
    for (auto& _b : bs) {
        if (_b.y < b.y && _b.h >= b.h && cover(_b, x)) return false;
    }
    return true;
}

int main() {
    int cases = 0;
    int n;
    while (scanf("%d", &n), n) {
        vector<building> v(n);
        vector<double> x_idx;
        int _id = 0;
        for (auto& b : v) {
            b.id = ++_id;
            scanf("%lf%lf%lf%*lf%lf", &b.x, &b.y, &b.w, &b.h);
            x_idx.push_back(b.x);
            x_idx.push_back(b.x + b.w);
        }
        sort(v.begin(), v.end());
        sort(x_idx.begin(), x_idx.end());
        x_idx.erase(unique(x_idx.begin(), x_idx.end()), x_idx.end());

        if (cases++) puts("");
        printf("For map #%d, the visible buildings are numbered as follows:\n",
               cases);
        printf("%d", v[0].id);
        for (int i = 1; i < v.size(); ++i) {
            bool vis = false;
            for (int j = 0; j < x_idx.size() - 1; ++j) {
                double mid = (x_idx[j] + x_idx[j + 1]) / 2.0;
                if (visible(v[i], mid, v)) {
                    vis = true;
                    break;
                }
            }
            if (vis) printf(" %d", v[i].id);
        }
        puts("");
    }
}
