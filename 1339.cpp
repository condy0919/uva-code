#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    string a, b;
    int cnt1[26], cnt2[26];
    while (cin >> a >> b) {
        memset(cnt1, 0, sizeof(cnt1));
        memset(cnt2, 0, sizeof(cnt2));
        for (int i = 0; i < a.length(); ++i)
            ++cnt1[a[i] - 'A'];
        for (int i = 0; i < b.length(); ++i)
            ++cnt2[b[i] - 'A'];
        sort(cnt1, cnt1 + 26);
        sort(cnt2, cnt2 + 26);
        cout << (std::equal(cnt1, cnt1 + 26, cnt2) ? "YES\n" : "NO\n");
    }

    return 0;
}
