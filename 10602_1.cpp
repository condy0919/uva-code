#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int T, N;
string a[100];
int ans;

int main()
{
    cin >> T;
    while (T-- > 0) {
        cin >> N;
        for (int i = 0; i < N; ++i)
            cin >> a[i];
        sort(a, a + N);
        ans = a[0].length();
        for (int i = 1; i < N; ++i) {
            int j;
            for (j = 0; j < a[i].length() && j < a[i-1].length() && a[i][j] == a[i-1][j]; ++j)
                ;
            ans += a[i].length() - j;
        }
        cout << ans << endl;
        for (int i = 0; i < N; ++i)
            cout << a[i] << endl;
    }
}
