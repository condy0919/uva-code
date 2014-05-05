#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

int p;
int a[100];
int target;
bool route[100][64001];

char conv(int x)
{
    static char op[] = "+-*/";
    return op[x];
}

/*
 * 如果在route[cur][s]中已经标记过了，说明已经有一次尝试并且不成功了，
 * 则可以将其剪掉，因为后面所有的运算组合都对这个结果产生不了
 * 符合要求的结果。
 */
bool dfs(int cur, int ans, vector<char>& op)
{
    if (cur == p)
        return ans == target;

    for (int _op = 0; _op < 4; ++_op) {
        int s = 32001;
        if (_op == 0)
            s = ans + a[cur];
        else if (_op == 1)
            s = ans - a[cur];
        else if (_op == 2)
            s = ans * a[cur];
        else if (ans % a[cur] == 0)
            s = ans / a[cur];
        if (abs(s) > 32000)
            continue;
        op.push_back(conv(_op));
        if (!route[cur][s] && dfs(cur + 1, s, op))
            return true;
        route[cur][s] = true;
        op.pop_back();
    }
    return false;
}

int main()
{
    int T;
    cin >> T;
    while (T-- > 0) {
        cin >> p;
        for (int i = 0; i < p; ++i)
            cin >> a[i];
        cin >> target;
        memset(route, 0, sizeof(route));
        vector<char> op;
        if (dfs(1, a[0], op)) {
            for (int i = 0; i < p - 1; ++i)
                cout << a[i] << op[i];
            cout << a[p - 1] << "=" << target << endl;
        } else {
            cout << "NO EXPRESSION" << endl;
        }
    }
    return 0;
}
