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
 * 明明就是一个dfs+记忆化搜索，就是想不到啊。。
 * http://www.cnblogs.com/xiaocai905767378/archive/2012/04/23/2466936.html
 * ^ 看了这里思路。原来是枚举每一个单词在一行中的位置。
 */

#define rep(i, s, e) for (int i = s; i <= e; ++i)
#define pre(i, s, e) for (int i = s; i >= e; --i)

#define pi (acos(-1.0))
#define eps (1e-9)
#define inf 0x7f7f7f7f

using namespace std;

int width;
vector<string> words;
int f[100000][81];

int dp(int i, int pos) {
    if (i == words.size())
        return f[i][pos] = 0;
    if (f[i][pos] != -1)
        return f[i][pos];

    f[i][pos] = inf;
    // single line
    if (pos == 0)
        f[i][pos] = min(f[i][pos], dp(i + 1, 0) + 500);
    // another case
    if (pos + words[i].length() == width)
        return f[i][pos] = min(f[i][pos], dp(i + 1, 0));
    int next_pos = pos + words[i].length() + 1;
    for (int j = next_pos; j < width; ++j) {
        if (i + 1 >= words.size() || j + words[i + 1].length() > width)
            break;
        int dis = j - next_pos;
        f[i][pos] = min(f[i][pos], dp(i + 1, j) + dis * dis);
    }
    return f[i][pos];
}

void print_ans(int i, int pos) {
    if (i == words.size())
        return;

    cout << words[i];
    if (f[i][pos] == f[i + 1][0] + 500) {
        cout << endl;
        return print_ans(i + 1, 0);
    }
    if (pos + words[i].length() == width) {
        cout << endl;
        return print_ans(i + 1, 0);
    }

    int next_pos = pos + words[i].length() + 1;
    for (int j = next_pos; j < width; ++j) {
        int dis = j - next_pos;
        if (i + 1 < words.size() && f[i][pos] == f[i + 1][j] + dis * dis) {
            cout << string(dis + 1, ' ');
            return print_ans(i + 1, j);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);

    string line;
    while (cin >> width, width) {
        cin.ignore();
        words.clear();
        while (getline(cin, line), !line.empty()) {
            istringstream iss(line);
            string word;
            while (iss >> word)
                words.push_back(word);
        }

        memset(f, -1, sizeof(f));
        dp(0, 0);
        print_ans(0, 0);
        cout << endl;
    }

    return 0;
}
