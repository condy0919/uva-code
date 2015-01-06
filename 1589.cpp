#include <iostream>
#include <algorithm>

using namespace std;

struct piece {
    char kind;
    int x, y;
} pieces[7];

const int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
const int horse_dx[] = {-2, -2, -1, 1, 2, 2, 1, -1},
          horse_dy[] = {-1, 1, 2, 2, 1, -1, -2, -2};

int N;
int b_x, b_y;

bool in_palace(int x, int y) {
    return x >= 1 && x <= 3 && y >= 4 && y <= 6;
}

int vertical_check(int x1, int x2, int y) {
    return count_if(pieces, pieces + N, [=](const piece &item) {
        return y == item.y && item.x > x1 && item.x < x2;
    });
}

int horizontal_check(int x, int y1, int y2) {
    return count_if(pieces, pieces + N, [=](const piece &item) {
        return x == item.x && item.y > y1 & item.y < y2;
    });
}

bool checkmate() {
    for (int i = 0; i < N; ++i) {
        if (pieces[i].x == b_x && pieces[i].y == b_y) // overlap
            continue;
        if (pieces[i].kind == 'G') { // 帅
            if (pieces[i].y == b_y &&
                vertical_check(b_x, pieces[i].x, b_y) == 0)
                return true;
        } else if (pieces[i].kind == 'R') { // 车
            if ((pieces[i].x == b_x &&
                 horizontal_check(b_x, min(b_y, pieces[i].y),
                                  max(b_y, pieces[i].y)) == 0) ||
                (pieces[i].y == b_y &&
                 vertical_check(min(b_x, pieces[i].x), max(b_x, pieces[i].x),
                                b_y) == 0))
                return true;
        } else if (pieces[i].kind == 'C') { // 炮
            if ((pieces[i].x == b_x &&
                 horizontal_check(b_x, min(b_y, pieces[i].y),
                                  max(b_y, pieces[i].y)) == 1) ||
                (pieces[i].y == b_y &&
                 vertical_check(min(b_x, pieces[i].x), max(b_x, pieces[i].x),
                                b_y) == 1))
                return true;
        } else if (pieces[i].kind == 'H') { // 马
            for (int dir = 0; dir < 8; ++dir) {
                int _x = pieces[i].x + horse_dx[dir],
                    _y = pieces[i].y + horse_dy[dir];
                int __x = pieces[i].x + dx[dir / 2],
                    __y = pieces[i].y + dy[dir / 2];
                if (_x == b_x && _y == b_y &&
                    count_if(pieces, pieces + N, [=](const piece &item) {
                        return item.x == __x && item.y == __y;
                    }) == 0)
                    return true;
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);

    while (cin >> N >> b_x >> b_y, N || b_x || b_y) {
        for (int i = 0; i < N; ++i)
            cin >> pieces[i].kind >> pieces[i].x >> pieces[i].y;
        bool win = true;
        for (int dir = 0; dir < 4; ++dir) {
            int _x = b_x + dx[dir], _y = b_y + dy[dir];
            if (!in_palace(_x, _y))
                continue;
            b_x = _x, b_y = _y;
            if (!checkmate()) {
                win = false;
                break;
            }
            b_x -= dx[dir];
            b_y -= dy[dir];
        }
        cout << (win ? "YES\n" : "NO\n");
    }

    return 0;
}
