#include <iostream>
#include <algorithm>

using namespace std;

#define N 500

int s[N];
int main()
{
    int T, r;
    cin >> T;
    while (T-- > 0) {
        cin >> r;
        for (int i = 0; i < r; ++i)
            cin >> s[i];
        sort(s, s + r);
        int mid = r / 2, d = 0;
        for (int i = 0; i < r; ++i)
            d += abs(s[i] - s[mid]);
        cout << d << endl;
    }

    return 0;
}
