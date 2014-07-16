#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <cstdint>
using namespace std;

string s;
const uint64_t limit = 0x7fffffff;
uint64_t f[201];
/*
 * f[i] = max{f[i], f[i - j] + num}
 * 可以从左向右推。
 */
void dp() {
    uint64_t v;
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '0') {
            f[i + 1] = max(f[i + 1], f[i]);
            continue;
        }
        v = 0;
        for (int j = i; j < s.length(); ++j) {
            v = 10 * v + s[j] - '0';
            if (v > limit)
                break;
            f[j + 1] = max(f[j + 1], f[i] + v);
        }
    }
}
int main() {
    int n;
    cin >> n;
    while (n-- > 0) {
        cin >> s;
        memset(f, 0, sizeof(f));
        dp();
        cout << f[s.length()] << endl;
    }
    return 0;
}
