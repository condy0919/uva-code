#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>

/*
 * 求lis。
 */

using namespace std;

struct elem {
    int x, y, z;

    elem(int _x=0, int _y=0, int _z=0):x(_x), y(_y), z(_z) {}

    bool operator<(const elem& rhs) const {
        if (x == rhs.x)
            return y < rhs.y;
        return x < rhs.x;
    }

    bool operator>(const elem& rhs) const {
        return x > rhs.x && y > rhs.y;
    }
};

int main() {
    int n, cases = 0;
    int f[200];

    while (cin >> n, n) {
        vector<elem> vec;
        elem v;
        for (int i = 0; i < n; ++i) {
            cin >> v.x >> v.y >> v.z;
            vec.push_back(v);
            vec.push_back(elem(v.x, v.z, v.y));
            vec.push_back(elem(v.y, v.x, v.z));
            vec.push_back(elem(v.y, v.z, v.x));
            vec.push_back(elem(v.z, v.x, v.y));
            vec.push_back(elem(v.z, v.y, v.x));
        }
        sort(vec.begin(), vec.end());
        for (int i = 0; i < vec.size(); ++i) {
            f[i] = vec[i].z;
            for (int j = 0; j < i; ++j) {
                if (vec[i] > vec[j])
                    f[i] = max(f[i], f[j] + vec[i].z);
            }
        }
        printf("Case %d: maximum height = %d\n", ++cases, *max_element(f, f + vec.size()));
    }
    return 0;
}
