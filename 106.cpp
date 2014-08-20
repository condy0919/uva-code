#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <bitset>
#include <utility>
#include <functional>
#include <numeric>
#include <limits>
#include <cmath>
#include <cctype>
#include <cstring>

/*
 * x = a^2 - b^2;
 * y = 2 * a * b;
 * z = a^2 + b^2;
 * 这个勾股数很早就知道了，然后这个是用来求解(x, y, z)互素情况下的。
 * 而且(a, b)也要互素。
 * ^ 关于这个的分析见：http://blog.csdn.net/metaphysis/article/details/6995250
 * 不在triple组内的数个数就要先生成所有的勾股数，再统计。
 */

#define rep(i, s, e) for (int i = s; i <= e; ++i)
#define pre(i, s, e) for (int i = s; i >= e; --i)

#define pi (acos(-1.0))
#define eps (1e-9)
#define inf 0x7f7f7f7f

using namespace std;

int gcd(int a, int b) {
    while (b > 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);

    int N;
    while (cin >> N) {
        int limit = sqrt(N);
        int ans = 0;
        bitset<1000001> vis;
        for (int i = 1; i <= limit; ++i) {
            for (int j = i + 1; j <= limit; j += 2) {
                if (i * i + j * j > N)
                    break;
                if (gcd(i, j) != 1)
                    continue;
                int a = j * j - i * i,
                    b = 2 * j * i,
                    c = j * j + i * i;
                ++ans;
                for (int k = 1; c * k <= N; ++k)
                    vis[k * a] = vis[k * b] = vis[k * c] = 1;
            }
        }
        cout << ans << " " << N - vis.count() << endl;
    }

    return 0;
}
