#include <iostream>
#include <algorithm>

#define inf 0x7f7f7f7f

/*
 * TODO: 有错误。
 */

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int T;
    int need, n1, n5, n10;
    cin >> T;
    while (T-- > 0) {
        cin >> need >> n1 >> n5 >> n10;

        if (n10 >= need) { // only 10
            cout << need << endl;
            continue;
        } else if (n10 + n5 / 2 >= need) { // only 10 and 5
            cout << n10 + (need - n10) * 2 << endl;
            continue;
        }
        int min = inf;
        for (int x = 0; x <= std::min(n10, (n1 + 2 * n10) / 5); ++x) {
            int y = std::max(0, (5 * x + 3 * n5 - 2 * n10 - n1 + 7) / 8);
            min = std::min(min, 2 * y - x);
        }
        cout << 8 * need - 7 * n10 - 4 * n5 + min << endl;
    }

    return 0;
}
