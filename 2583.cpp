#include <iostream>
#include <istream>
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
 * http://blog.csdn.net/a342374071/article/details/6689232
 * ^ 好棒的思路。
 */

#define rep(i, s, e) for (int i = s; i <= e; ++i)
#define pre(i, s, e) for (int i = s; i >= e; --i)

#define pi (acos(-1.0))
#define eps (1e-9)
#define inf 0x7f7f7f7f

using std::cout;
using std::cin;
using std::ios;
using std::pair;
using std::max;
using std::endl;

int left[101], right[101];
char s[101];

bool less(const pair<int, int>& t1, const pair<int, int>& t2) {
    int i = t1.first, j = t2.first;
    while (s[i] == '0')
        ++i;
    while (s[j] == '0')
        ++j;
    if (t1.second - i != t2.second - j)
        return t1.second - i < t2.second - j;
    while (i < t1.second) {
        if (s[i] != s[j])
            return s[i] < s[j];
        ++i, ++j;
    }
    return false;
}

void print_ans(int len) {
    int p = right[0];
    for (int i = 0; i < len; ) {
        while (i < p && i < len)
            cout << s[i++];
        if (i < len)
            cout << ",";
        p = right[p];
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);

    while (cin.getline(s, 101)) {
        int len = std::strlen(s);
        if (len == 1 && s[0] == '0')
            break;

        memset(left, 0, sizeof(left));
        memset(right, 0, sizeof(right));
        
        for (int i = 1; i < len; ++i)
            for (int j = 0; j < i; ++j)
                if (less({left[j], j + 1}, {j + 1, i + 1}))
                    left[i] = j + 1;

        int tlen = left[len - 1];
        right[tlen] = right[tlen + 1] = len;

        for (int i = tlen - 1; s[i] == '0'; --i)
            right[i] = len;

        for (int i = tlen - 1; i >= 0; --i)
            for (int j = i; j <= tlen; ++j)
                if (less({i, j}, {j, right[j]}))
                    right[i] = max(right[i], j);

        print_ans(len);
    }

    return 0;
}
