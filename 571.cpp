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

/*
 * 一开始这个想法没有想到啊。
 *
 * 一个[0, b-1] 到 [0, b-1]的映射关系。
 * Proof.
 *   r = a * k % b. 当k从[0,b-1]中取值时，r的值域在[0,b-1].
 *
 *   r1 = a * k1 % b, r2 = a * k2 % b;
 *   如果k1 != k2, 假设r1 == r2.
 *   则 r1 - r2 = a * (k1 - k2) % b. => b | (k1 - k2),
 *   而k1, k2 \in [0, b - 1], 则上式不成立。
 *   综上, 假设不成立。即k1 != k2, 则r1 != r2.
 *
 *   这样就可以证明k <=> r 是一个满射关系。
 *   即r的取值可以取遍[0, b - 1]中的任何值。
 *   这样的话，只要一直将a中的水倒入b中就可以了。
 */

using namespace std;

int ca, cb, n;

int main() {
    ios::sync_with_stdio(false);

    while (cin >> ca >> cb >> n) {
        int a = 0, b = 0;
        if (n == cb) {
            cout << "fill B\n" "success" << endl;
            continue;
        }
        while (b != n) {
            a = ca;
            cout << "fill A\n" "pour A B" << endl;
            if (b + a >= cb) {
                cout << "empty B\n" "pour A B" << endl;
                b = (b + a) % cb;
                a = 0;
            } else {
                b += a;
                a = 0;
            }
        }
        cout << "success" << endl;
    }

    return 0;
}
