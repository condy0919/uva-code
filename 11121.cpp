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
 * 简单的数学题.
 */


using namespace std;

string negate2(int x) {
    string ret;
    do {
        ret += '0' + (x & 1);
        x = (x - (x & 1)) / -2;
    } while (x != 0);
    reverse(ret.begin(), ret.end());
    return std::move(ret);
}

int main() {
    ios::sync_with_stdio(false);

    int N, x;
    cin >> N;
    for (int cases = 0; cases < N; ++cases) {
        cin >> x;
        cout << "Case #" << cases + 1 << ": " << negate2(x) << endl;
    }

    return 0;
}
