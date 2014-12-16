#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int T;
string s;

bool period(int step) {
    const string& _s = s.substr(0, step);
    for (int i = step; i < s.length(); i += step)
        if (s.substr(i, step) != _s)
            return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T-- > 0) {
        cin >> s;
        int ans;
        for (ans = 1; ans < s.length(); ++ans)
            if (period(ans))
                break;
        cout << ans << endl;
        if (T)
            cout << endl;
    }
    return 0;
}
