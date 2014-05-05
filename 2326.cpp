#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int road[201];

void mark(int l, int r) {
    if (l > r) {
        mark(r, l);
        return;
    }
    for (int i = l; i <= r; ++i)
        ++road[i];
}

int main() {
    int T, N, x, y;

    cin >> T;
    while (T-- > 0) {
        cin >> N;
        memset(road, 0, sizeof(road));
        for (int i = 0; i < N; ++i) {
            cin >> x >> y;
            x = (x + 1) / 2;
            y = (y + 1) / 2;
            mark(x, y);
        }
        cout << 10 * *max_element(road + 1, road + 201) << endl;;
    }
    return 0;
}
