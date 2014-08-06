#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <cstring>

/*
 * 一开始没有想到是用LIS做，想了好久。
 * d[x][y]表示路径最长大小。则d[x][y] = max(d[x-1][y], d[x][y-1]) + (1 if (x, y) is garbage else 0)
 * 这个很好计算，然而后面的条数就不好做了，就一直坑在这边了。
 * 然后看了这里：http://www.cnblogs.com/kedebug/archive/2012/11/26/2789051.html
 * 感觉比较巧妙的一点就是将(row, col)这个点也给标记garbage了。。
 * 还有测试数据是有重复数据的。。。
 */

using namespace std;

int row, col;
int x, y;
bool g[101][101];
int d[101 * 101], t[101 * 101];
int parent[101 * 101];

int main() {
    ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> row >> col, row != -1 || col != -1) {
        vector<pair<int, int> > coords;
        memset(g, 0, sizeof(g));
        while (cin >> x >> y, x && y)
            g[x][y] = true;
        for (int i = 1; i <= row; ++i)
            for (int j = 1; j <= col; ++j)
                if (g[i][j])
                    coords.push_back({i, j});
        bool extra = !g[row][col];
        if (extra)
            coords.push_back({row, col});
        for (int i = 0; i < coords.size(); ++i) {
            d[i] = t[i] = 1;
            parent[i] = -1;
            for (int j = 0; j < i; ++j) {
                if (coords[i].second < coords[j].second)
                    continue;
                if (d[i] < d[j] + 1)
                    d[i] = d[j] + 1, t[i] = t[j], parent[i] = j;
                else if (d[i] == d[j] + 1)
                    t[i] += t[j];
            }
        }
        cout << "CASE#" << ++cases << ": " << d[coords.size() - 1] - extra << " ";
        cout << t[coords.size() - 1];
        vector<int> output;
        for (int i = coords.size() - 1; i != -1; i = parent[i]) {
            if (!extra || i != coords.size() - 1)
                output.push_back((coords[i].first - 1) * col + coords[i].second);
        }
        for (int i = output.size() - 1; i >= 0; --i)
            cout << " " << output[i];
        cout << endl;
    }

    return 0;
}
