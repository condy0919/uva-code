#include <iostream>
#include <cmath>

/*
 * 好奇怪啊，明明这题有公式解，却怎么也不能AC。明明都已经列出来了，分类讨论也好了，就是不对。
 */

using namespace std;

int main()
{
    double m, p, a, b;
    while (cin >> m >> p >> a >> b) {
        double ab = a * b, ans = 0;
        for (int i = 0; i < m - 1; ++i) {
            if (ab < a) {
                ++ab;
                ++ans;
            } else {
                ab -= a;
                ans += pow(a, p);
            }
        }
        ans += pow(ab, p);
        ans /= pow(sqrt(a), p);
        cout << int(ans + 0.5) << endl;
    }
    return 0;
}
