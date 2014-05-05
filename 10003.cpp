#include <iostream>
#include <algorithm>
#include <limits>
#include <cstring>

using namespace std;

int len, n, pos[1001];
int cache[1001][1001];

int dp(int start, int end) {
    if (start + 1 >= end)
        return 0;
    if (cache[start][end])
        return cache[start][end];

    int ret = end - start, _min = numeric_limits<int>::max();
    bool flag = false;
    for (int i = start + 1; i < end; ++i) {
        if (!pos[i])
            continue;
        flag = true;
        _min = min(_min, dp(start, i) + dp(i, end));
    }
    if (!flag)
        return cache[start][end] = 0;
    return cache[start][end] = ret + _min;
}

int main() {
    int v;
    while (cin >> len, len) {
        cin >> n;
        memset(pos, 0, sizeof(pos));
        memset(cache, 0, sizeof(cache));
        for (int i = 0; i < n; ++i) {
            cin >> v;
            pos[v] = true;
        }
        cout << "The minimum cutting is " << dp(0, len) << "." << endl;
    }
    return 0;
}
