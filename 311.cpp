#include <iostream>
#include <algorithm>
#include <cmath>
/*
 * 似乎g++优化导致错误了。
 * 另，看的是这里的题解：http://hi.baidu.com/knowledgetime/item/da54577d12e90123d6a89ce5
 * 本来以为是dfs，没有想到竟然可以这样做。就算想到了也不敢写啊。果然自信心需要加强，
 * 思路仍然不够开阔。
 */
using namespace std;
const int one[4] = {0,7,6,5}, two[4] = {0,5,3,1};
bool read(int a[]) {
    int v, s = 0;
    for (int i = 1; i <= 6; ++i) {
        cin >> v;
        s += (a[i] = v);
    }
    return s == 0 ? false : true;
}
int main() {
    int a[7], ans;
    while (read(a)) {
        ans = a[6] + a[5] + a[4] + (a[3]+3)/4;

        int exp2 = 5 * a[4] + two[a[3] % 4], exp1 = a[5] * 11 + one[a[3] % 4];
        if (a[2] > exp2) {
            int left = a[2] - exp2;
            ans += (left+8)/9;
            exp1 += 36 - (left % 9) * 4;
        } else {
            exp1 += 4 * (exp2 - a[2]);
        }
        if (a[1] > exp1) {
            ans += (a[1] - exp1 +35)/36;
        }
        cout << ans << endl;
    }
    return 0;
}
