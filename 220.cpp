#include <cstdio>
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

using namespace std;

char G[11][11];
int white, black;
char cur;
char cmd;

inline char opposite(char color) {
    return 'W' + 'B' - color;
}

bool exist(int x, int y, int dx, int dy) {
    while (x >= 1 && x <= 8 && y >= 1 && y <= 8 && G[x][y] == opposite(cur)) {
        x += dx;
        y += dy;
    }
    if (x >= 1 && x <= 8 && y >= 1 && y <= 8)
        return G[x][y] == cur;
    return false;
}

bool legal(int x, int y) {
    if (G[x][y] == 'W' || G[x][y] == 'B')
        return false;

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0)
                continue;
            int _x = x + dx, _y = y + dy;
            if (_x < 1 || _y < 1 || _x > 8 || _y > 8)
                continue;
            if (G[_x][_y] == cur || G[_x][_y] == '-')
                continue;
            if (exist(_x, _y, dx, dy))
                return true;
        }
    }
    return false;
}

void list_all_moves() {
    bool first = true;
    for (int i = 1; i <= 8; ++i) {
        for (int j = 1; j <= 8; ++j) {
            if (legal(i, j)) {
                if (first)
                    first = false;
                else
                    printf(" ");
                printf("(%d,%d)", i, j);
            }
        }
    }
    if (first)
        printf("No legal move.");
    puts("");
}

void flip(int x, int y, int dx, int dy) {
    int& pl = (cur == 'W' ? white : black);
    int& op = (cur == 'W' ? black : white);
    while (G[x][y] != cur) {
        G[x][y] = cur;
        ++pl;
        --op;
        x += dx;
        y += dy;
    }
}

void mark(int x, int y) {
    G[x][y] = cur;
    if (cur == 'W')
        ++white;
    else
        ++black;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0)
                continue;
            int _x = x + dx, _y = y + dy;
            if (_x < 1 || _y > 8 || _y < 1 || _y > 8)
                continue;
            if (G[_x][_y] == cur || G[_x][_y] == '-')
                continue;
            if (exist(_x, _y, dx, dy))
                flip(_x, _y, dx, dy);
        }
    }
    printf("Black - %2d White - %2d\n", black, white);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        white = black = 0;
        for (int i = 1; i <= 8; ++i)
            scanf("%s", &G[i][1]);
        for (int i = 1; i <= 8; ++i) {
            for (int j = 1; j <= 8; ++j) {
                if (G[i][j] == 'W')
                    ++white;
                else if (G[i][j] == 'B')
                    ++black;
            }
        }
                
        scanf(" %c", &cur);
        while (scanf(" %c", &cmd), cmd != 'Q') {
            if (cmd == 'L') {
                list_all_moves();
            } else if (cmd == 'M') {
                char x, y;
                scanf("%c%c", &x, &y);
                if (!legal(x - '0', y - '0'))
                    cur = 'B' + 'W' - cur;
                mark(x - '0', y - '0');
                cur = 'B' + 'W' - cur;
            }
        }
        for (int i = 1; i <= 8; ++i)
            puts(&G[i][1]);
        
        if (T)
            puts("");
    }

    return 0;
}
