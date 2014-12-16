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

#define rep(i, s, e) for (int i = s; i <= e; ++i)
#define pre(i, s, e) for (int i = s; i >= e; --i)

#define pi (acos(-1.0))
#define eps (1e-9)
#define inf 0x7f7f7f7f

using namespace std;

char G[5][6];

int main() {
    ios::sync_with_stdio(false);

    bool first = true;
    int cases = 1;
    while (true) {
        cin.getline(G[0], 6, '\n');
        if (strcmp(G[0], "Z") == 0)
            break;
        for (int i = 1; i < 5; ++i)
            cin.getline(G[i], 6);

        if (first)
            first = false;
        else
            cout << endl;
        cout << "Puzzle #" << cases++ << ":\n";

        int x, y;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (G[i][j] == ' ') {
                    x = i;
                    y = j;
                    break;
                }
            }
        }

        int ch;
        bool err = false;
        while ((ch = cin.get()) != '0') {
            int _x = x, _y = y;
            if (ch == 'A') {
                --x;
            } else if (ch == 'B') {
                ++x;
            } else if (ch == 'L') {
                --y;
            } else if (ch == 'R') {
                ++y;
            }
            if (x < 0 || x >= 5 || y < 0 || y >= 5)
                err = true;
            if (!err)
                swap(G[x][y], G[_x][_y]);
        }
        cin.ignore();
        if (err) {
            cout << "This puzzle has no final configuration.\n";
            continue;
        }
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 4; ++j)
                cout << G[i][j] << " ";
            cout << G[i][4] << endl;
        }
    }

    return 0;
}
