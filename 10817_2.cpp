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
#include <sstream>

/*
 * 看了这里，原来还有更加简便的方法http://blog.csdn.net/shuangde800/article/details/9776645
 * 主要是通过当前这个状态来更新下一个状态.
 */

#define rep(i, s, e) for (int i = s; i <= e; ++i)
#define pre(i, s, e) for (int i = s; i >= e; --i)

#define pi (acos(-1.0))
#define eps (1e-9)
#define inf 0x7f7f7f7f

using namespace std;

string line;
int S, M, N;
int f[1<<8][1<<8];
int p[101], w[101];
int c, sub;


int main() {
    ios::sync_with_stdio(false);

    while (cin >> S >> M >> N, S) {
        cin.ignore();

        int total = 0, cnt[8] = {0};
        for (int i = 0; i < M; ++i) {
            getline(cin, line);
            istringstream iss(line);
            iss >> c;
            total += c;
            while (iss >> sub)
                ++cnt[sub - 1];
        }
        memset(p, 0, sizeof(p));
        for (int i = 0; i < N; ++i) {
            getline(cin, line);
            istringstream iss(line);
            iss >> w[i];
            while (iss >> sub)
                p[i] |= (1 << (sub - 1));
        }

        int s1 = 0, s2 = 0;
        for (int i = 0; i < S; ++i) {
            if (cnt[i] >= 2) {
                s2 |= (1 << i);
                s1 |= (1 << i);
            } else if (cnt[i] >= 1) {
                s1 |= (1 << i);
            }
        }

        memset(f, 0x3f, sizeof(f));
        f[s1][s2] = total;
        const int P = (1 << S) - 1;
        for (int i = 0; i < N; ++i) {
            for (int j1 = P; j1 >= 0; --j1) {
                for (int j2 = P; j2 >= 0; --j2) {
                    int n1 = j1 | p[i], n2 = (j1 & p[i]) | j2;
                    f[n1][n2] = min(f[n1][n2], f[j1][j2] + w[i]);
                }
            }
        }
        cout << f[P][P] << endl;
    }

    return 0;
}
