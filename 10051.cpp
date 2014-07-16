#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

#define N 501
#define COLORS 101
#define inf 0x7f7f7f7f

/*
 * 状态表示: f[i][c]表示前i个物品以c颜色为结尾可达成的最大值。
 * 则f[i][c] = f[j][oppo_color(c)], 其中oppo_color代表某颜色对面的值， j < i.
 */

enum {FRONT, BACK, LEFT, RIGHT, TOP, BOTTOM};
const char* faces[] = {
    "front", "back", "left", "right", "top", "bottom"
};

int colors[N][6];
int f[N][COLORS];
pair<int, int> parent[N][COLORS];
int n;

int oppo(int c) {
    if (c % 2)
        return c - 1;
    return c + 1;
}

int cur_color(int i, int face) {
    return colors[i][face];
}

int oppo_color(int i, int face) {
    return cur_color(i, oppo(face));
}

void print_ans(pair<int, int>& end) {
    int idx = end.first, face = end.second;

    if (idx == -1)
        return;
    print_ans(parent[idx][face]);
    cout << idx + 1 << " " << faces[oppo(face)] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    bool first = true;
    int cases = 0;
    while (cin >> n, n) {
        if (first)
            first = false;
        else
            cout << endl;

        for (int i = 0; i < n; ++i)
            fill(f[i], f[i] + COLORS, inf);
        for (int i = 0; i < n; ++i)
            fill(parent[i], parent[i] + COLORS, make_pair(-1, -1));

        cout << "Case #" << ++cases << endl;
        for (int i = 0; i < n; ++i)
            cin >> colors[i][0] >> colors[i][1] >> colors[i][2] >> colors[i][3] >> colors[i][4] >> colors[i][5];

        for (int i = 0; i < n; ++i) {
            for (int ic = 0; ic < 6; ++ic) {
                f[i][ic] = 1;
                for (int j = 0; j < i; ++j) {
                    for (int jc = 0; jc < 6; ++jc) {
                        if (cur_color(j, jc) != oppo_color(i, ic))
                            continue;
                        if (f[i][ic] < f[j][jc] + 1) {
                            f[i][ic] = f[j][jc] + 1;
                            parent[i][ic] = make_pair(j, jc);
                        }
                    }
                }
            }
        }
        int ans = 0;
        pair<int, int> end;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < 6; ++j)
                if (ans < f[i][j]) {
                    ans = f[i][j];
                    end = {i, j};
                }

        cout << ans << endl;
        print_ans(end);
    }
    return 0;
}
