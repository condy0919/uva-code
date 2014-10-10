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

/*
 * 一开始思路都没有，一直在朝递推这个方向上想了.._(:з」∠)_
 * http://www.cnblogs.com/staginner/archive/2011/12/20/2295126.html
 * http://hi.baidu.com/knowledgetime/item/87d13b1f12290a53f1090ea7
 * 参考上面这2个..
 */


using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    int p[4] = {0, 2, 4, 4};
    while (cin >> n >> m, n || m) {
        int _1 = std::max(n, m), _2 = std::min(n, m);
        if (_2 >= 3)
            cout << (_1 * _2 + 1) / 2;
        else if (_2 == 2)
            cout << (_1 / 4) * 4 + p[(_1 % 4)];
        else
            cout << _1;
        cout << " knights may be placed on a " << n << " row " << m << " column board." << endl;
    }

    return 0;
}
