#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/*
 * 一开始题目意思理解错了，以为比第一个len, weight都大的都不用时间了。2333
 */

struct stick_t {
    int len, weight;
};

bool cmp(const stick_t& a, const stick_t& b) {
    if (a.len == b.len)
        return a.weight < b.weight;
    return a.len < b.len;
}

int solve(vector<stick_t>& a) {
    int cnt = 0;
    sort(a.begin(), a.end(), cmp);
    while (!a.empty()) {
        int weight = a[0].weight;
        for (int i = 0; i < a.size(); ++i)
            if (a[i].weight >= weight) {
                weight = a[i].weight;
                a.erase(a.begin() + i);
                --i;
            }
        ++cnt;
    }
    return cnt;
}

int main() {
    int T, n;
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        vector<stick_t> a(n);
        for (int i = 0; i < n; ++i)
            cin >> a[i].len >> a[i].weight;
        cout << solve(a) << endl;
    }
    return 0;
}
