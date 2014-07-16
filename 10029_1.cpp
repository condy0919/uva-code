#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <vector>

/*
 * 由于题目给出的数据就是字典序的，就省得我们排序了。(´・ω・｀)
 * 本来想采用lis那样的方法，发现得到2个字符串之间的关系有点难。
 * 于是参考网上的，将当前第i个字符串所能做的所有变换字符串都找
 * 出来，看这些结果是否与前面的某个字符串匹配。若匹配了，则更新
 * 长度。
 * http://www.cnblogs.com/kedebug/archive/2012/11/21/2780846.html
 * ^ 这个是记忆化搜索的版本，而且自己手工实现了hash.
 *
 * 
 * 我把它改成迭代了，hash是直接了C++11的unordered_map，它内置hash.
 * 我本来想直接用unordered_set的，但是无法知道当前与之相同的最长路，
 * 所以用了unordered_map, 增加了下标。
 *
 * 这里std::move是C++11里面的东西，有了这个可以将左值变成右值，会有
 * 稍许的优化。
 */

using namespace std;

int dp[25001];

string tras(const string& s, char ch, int pos, int type) {
    if (type == 0)
        return std::move(string(s).replace(pos, 1, 1, ch));
    if (type == 1)
        return std::move(string(s).insert(pos, 1, ch));
    string ret(s);
    ret.erase(ret.begin() + pos);
    return std::move(ret);
}

int main() {
    ios::sync_with_stdio(false);
    unordered_map<string, int> tbl;
    vector<string> svec;
    string s;

    while (cin >> s)
        svec.push_back(s);

    int ans = 0;
    for (int i = 0; i < svec.size(); ++i) {
        dp[i] = 1;
        // replace | insert.
        for (int t = 0; t < 2; ++t)
            for (int j = 0; j < svec[i].length(); ++j)
                for (char ch = 'a'; ch <= 'z'; ++ch) {
                    s = tras(svec[i], ch, j, t);
                    if (s > svec[i])
                        break;
                    auto iter = tbl.find(s);
                    if (iter != tbl.end())
                        dp[i] = max(dp[i], dp[iter->second] + 1);
                }
        // delete.
        for (int j = 0; j < svec[i].length(); ++j) {
            s = tras(svec[i], 0, j, 2);
            auto iter = tbl.find(s);
            if (iter != tbl.end())
                dp[i] = max(dp[i], dp[iter->second] + 1);
        }
        ans = max(ans, dp[i]);
        tbl[svec[i]] = i;
    }
    cout << ans << endl;

    return 0;
}
