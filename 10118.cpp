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

using namespace std;

/*
 * pocket_states[p0, p1, p2, p3]表示piles{0~3}的指针处于p0~3时所能够获取的最大糖果数。
 * 则dp(p0,p1,p2,p3, 篮子里的糖果状态) = 尝试p_i, 可行则放入篮子 -> 若篮子中已有相同颜色的，则+1
 *                                                               -> 若没有相同颜色，不做什么
 *                                       p_i += 1, 之后继续递归, p_i -= 1.
 */

int n;
int piles[4][40];
bool vis[41][41][41][41];
int pocket_states[41][41][41][41];

int count(int x) {
    int ret = 0;
    while (x > 0) {
        ++ret;
        x &= (x - 1);
    }
    return ret;
}

int dp(int p0, int p1, int p2, int p3, int basket) {
    bool& flag = vis[p0][p1][p2][p3];
    int& res = pocket_states[p0][p1][p2][p3];
    if (flag)
        return res;
    if (count(basket) == 5) {
        flag = true;
        return res = 0;
    }

    int* a[] = {&p0, &p1, &p2, &p3};
    for (int i = 0; i < 4; ++i) {
        int* top = a[i];
        if (*top < n) {
            int item_color = piles[i][*top];
            ++*top;
            int t = dp(p0, p1, p2, p3, basket ^ (1 << item_color)) + ((basket & (1 << item_color)) != 0);
            res = max(res, t);
            --*top;
        }
    }
    flag = true;
    return res;
}

int main() {
    ios::sync_with_stdio(false);

    while (cin >> n, n) {
        memset(vis, 0, sizeof(vis));
        memset(pocket_states, 0, sizeof(pocket_states));
        for (int i = 0; i < n; ++i)
            cin >> piles[0][i] >> piles[1][i] >> piles[2][i] >> piles[3][i];
        cout << dp(0, 0, 0, 0, 0) << endl;
    }

    return 0;
}
