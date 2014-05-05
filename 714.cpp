#include <iostream>
#include <algorithm>
#include <numeric>
#include <cstring>
#include <stdint.h>

/*
 * 这个是lrj书上的原题。
 * 没有考虑到overflow的问题，竟然导致了Time limit...
 */

using namespace std;

#define N 501

int a[N];
bool slash[N]; // before position i exist '/' symbol

int64_t bin_search(int64_t, int64_t, int, int);
int div_(int64_t, int, int);
void output(int, int, int);

// [lo, hi]
int64_t bin_search(int64_t lo, int64_t hi, int k, int m)
{
    int64_t mid;
    while (lo < hi) {
        mid = lo + (hi - lo) / 2;
        if (div_(mid, k, m) <= k) // mid is large
            hi = mid;
        else
            lo = mid + 1;
    }
    return hi;
}

int div_(int64_t x0, int k, int m)
{
    int i = m - 1, parts = 0;
    memset(slash, 0, sizeof(slash));
    while (i >= 0) {
        int64_t s = 0;
        while (i >= 0 && s + a[i] <= x0 && parts + i >= k - 1) {
            s += a[i];
            --i;
        }
        /*
           100 200 300 400 500 600 700 800 900
           i ^ i+1 
           */
        slash[i + 1] = true;
        ++parts;
    }
    return parts;
}

void output(int64_t x0, int k, int m)
{
    // reconstruct slash position
    div_(x0, k, m);

    cout << a[0];
    for (int i = 1; i < m; ++i) {
        if (slash[i])
            cout << " /";
        cout << " " << a[i];
    }
    cout << endl;
}

// k parts, total m books
int main()
{
    int T;
    int k, m;

    cin >> T;
    while (T--) {
        cin >> m >> k;
        for (int i = 0; i < m; ++i)
            cin >> a[i];

        int64_t x = bin_search(*max_element(a, a + m), accumulate(a, a + m, int64_t(0)), k, m);
        output(x, k, m);
    }
    return 0;
}
