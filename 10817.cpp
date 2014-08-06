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
 * 一看到这题目就想到了01背包，判断第n个人时选或不选。
 * 以前还不知道可以套模型。。。
 *
 * 既然是01背包，只要找相应地对应于体积的特征就好了。无奈想不
 * 出来啊。。。
 *
 * 后百度找到了这个解答：http://www.cnblogs.com/staginner/archive/2011/12/07/2278727.html
 * 感觉写得十分详细。现按照我自己的思路转述一下。
 *
 * 题目里面只有费用以及每门课至少要有2个老师。
 * 如果拿费用当体积来算，那只有把每课的老师数来当价值了，这样明显不可取。
 * 因为我们要求的就是最小费用呀。(。・_・。)
 * 
 * 如果拿每课的老师数来当体积，把费用来当做价值，看起来好像简单很多。
 * f[n][?] = min{f[n-1][??], f[n-1][?]}
 *               ^ 聘用n     ^ 不聘用n
 * 那这里的？和？？到底代表什么呢。当然要和“每门课至少要有2个老师”相关。
 * 如果把？表示为每门课当前的老师数，则？？就等于？-S[n]。。S[n]代表第n个应聘者能够教的课程是什么。
 * 似乎状态转移方程找到了呢，不过怎么初始化初始状态呢?
 * 注意到还有一个条件没有用到，那就是正在服务的老师必须要聘用，则可以根据这么老师来算出每门课至少还需要
 * 多少老师教。那比这个状态还大的状态就可以理解为正在服务的老师有些并没有工作。 DAZE
 * f[n][c1][c2][c3][c4][c5][c6][c7][c8] <- 如果这样来的话肯定会memory exceed.
 * 由于每门课多于2人教可以看过正好2人，这样就可以把c1~c8这个状态转换为一个整数。
 * 所以f[n][s] = min{f[n-1][s | S[n]] + w[n], f[n-1][s}
 *                   ^ 聘用n           ^ 不聘用n
 * so, let's implement it.
 */

#define rep(i, s, e) for (int i = s; i <= e; ++i)
#define pre(i, s, e) for (int i = s; i >= e; --i)

#define pi (acos(-1.0))
#define eps (1e-9)
#define inf 0x7f7f7f7f

using namespace std;

int S, M, N;
int f[101][6562]; // 3^8
int w[101];
int applicants[101][8];
string line;
int c, sub;

int* base3(int val) {
    static int buf[8];
    for (int i = 0; i < S; ++i) {
        buf[i] = val % 3;
        val /= 3;
    }
    return buf;
}

bool ok(int buf[], int need[]) {
    for (int i = 0; i < S; ++i)
        if (buf[i] < need[i])
            return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);

    while (cin >> S >> M >> N, S) {
        cin.ignore();

        int total = 0, need[8] = {2,2,2,2,2,2,2,2};
        for (int i = 0; i < M; ++i) {
            getline(cin, line);
            istringstream iss(line);
            iss >> c;
            total += c;
            while (iss >> sub)
                if (need[sub - 1])
                    --need[sub - 1];
        }
        memset(applicants, 0, sizeof(applicants));
        for (int i = 1; i <= N; ++i) {
            getline(cin, line);
            istringstream iss(line);
            iss >> w[i];
            while (iss >> sub)
                applicants[i][sub - 1] = 1;
        }
        // initialize 
        memset(f, 0x3f, sizeof(f));
        const int UP_BOUND = pow(3, S);
        for (int i = 0; i < UP_BOUND; ++i) {
            if (ok(base3(i), need))
                f[0][i] = total;
        }

        for (int n = 1; n <= N; ++n) {
            for (int c = 0; c < UP_BOUND; ++c) {
                f[n][c] = f[n - 1][c]; // case 1: skip it

                int* buf = base3(c);
                for (int i = 0; i < S; ++i)
                    if (applicants[n][i] && buf[i] < 2)
                        ++buf[i];
                int k = 0;
                for (int i = S - 1; i >= 0; --i)
                    k = 3 * k + buf[i];
                f[n][c] = min(f[n][c], f[n - 1][k] + w[n]);
            }
        }
        cout << f[N][0] << endl;
    }

    return 0;
}
