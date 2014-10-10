#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>

/*
 * 一开始是用整个公周期算的，必然超时。
 * 后来想想，每个字符都有其各自的周期....
 */

using namespace std;

string s;
int k;
int n;
int p[200];
int cycle[200];

string map(const string& s, int k) {
    string ret(s.length(), '\0');
    for (int i = 0; i < s.length(); ++i) {
        int t = i;
        for (int j = 0; j < k % cycle[i]; ++j)
            t = p[t];
        ret[t] = s[i];
    }
    return std::move(ret);
}

int main() {
    ios::sync_with_stdio(false);

    while (cin >> n, n) {
        for (int i = 0; i < n; ++i) {
            cin >> p[i];
            --p[i];
        }

        memset(cycle, 0, sizeof(cycle));
        int b[200];
        iota(b, b + n, 0);
        for (int i = 0; i < n; ++i) {
            int cur, next = i;
            do {
                cur = next;
                next = p[cur];
                ++cycle[i];
            } while (i != next);
        }

        while (cin >> k, k) {
            cin.ignore();
            getline(cin, s);
            if (s.length() < n)
                s += std::move(string(n - s.length(), ' '));
            cout << map(s, k) << endl;
        }
        cout << endl;
    }

    return 0;
}
