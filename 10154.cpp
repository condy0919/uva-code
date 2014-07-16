#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct turtle {
    int weight, strength;
    bool operator<(const turtle& rhs) const {
        return strength < rhs.strength;
    }
};

#define N 5610
#define inf 0x7f7f7f7f

/*
 * f[i][j]代表前i只乌龟到达j层时所花费的最小重量。
 * 则f[i][j] = min{f[i-1][j], f[i-1][j-1] + w[i]}，当然s[i]能够承受自身以及f[i-1][j-1]的重量。
 * http://www.cnblogs.com/staginner/archive/2011/11/30/2268497.html
 * ^ 这个是更优的解法，使用了更少的空间。
 */
int f[N][N];

int main() {
    ios::sync_with_stdio(false);

    int w, s;
    vector<turtle> turtles(1);
    while (cin >> w >> s)
        if (w <= s)
            turtles.push_back({w, s});
    sort(turtles.begin(), turtles.end());
    for (int i = 0; i <= turtles.size(); ++i) {
        f[i][0] = 0;
        fill(f[i] + 1, f[i] + turtles.size() + 1, inf);
    }

    for (int i = 1; i <= turtles.size(); ++i) {
        for (int j = 1; j <= turtles.size(); ++j) {
            f[i][j] = f[i - 1][j];
            if (f[i - 1][j - 1] != inf && turtles[i].strength - turtles[i].weight >= f[i - 1][j - 1])
                f[i][j] = min(f[i][j], f[i - 1][j - 1] + turtles[i].weight);
        }
    }
    for (int i = turtles.size(); i >= 1; --i)
        if (f[turtles.size()][i] != inf) {
            cout << i << endl;
            break;
        }

    return 0;
}
