#include <iostream>
#include <algorithm>
#include <numeric>
#include <cstring>

using namespace std;

#define MAXSIZE 77

int N;
int a[MAXSIZE + MAXSIZE][MAXSIZE];
int line[MAXSIZE];
int _max;

int minsum(int a[], int n)
{
    int s = 0, ret = a[0];
    for (int i = 0; i < n; ++i) {
        s = s < 0 ? s + a[i] : a[i];
        ret = min(ret, s);
    }
    return ret;
}

int maxsum(int a[], int n)
{
    int s = 0, r1 = a[0], r2;
    for (int i = 0; i < n; ++i) {
        s = s > 0 ? s + a[i] : a[i];
        r1 = max(r1, s);
    }
    r2 = accumulate(a, a + n, 0) - minsum(a + 1, n - 2);
    return max(r1, r2);
}

int main()
{
    int T, v;
    
    cin >> T;
    while (T-- > 0) {
        cin >> N;
        for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= N; ++j) {
                cin >> v;
                a[i][j] = a[i + N][j] = v;
            }
        for (int j = 1; j <= N; ++j)
            for (int i = 1; i <= N + N - 1; ++i)
                a[i + 1][j] += a[i][j];
        _max = a[1][1];
        for (int i = 1; i <= N; ++i)
            for (int j = i; j < i + N; ++j) {
                for (int k = 1; k <= N; ++k)
                    line[k - 1] = a[j][k] - a[i - 1][k];
                _max = max(_max, maxsum(line, N));
            }
        cout << _max << endl;
    }

    return 0;
}
