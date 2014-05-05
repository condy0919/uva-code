#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

int n;
int a[10000];

struct cmp {
    int n;

    cmp(int _n):n(_n) {}
    bool operator()(int& x) {
        return x >= n;
    }
};

bool solve()
{
    for (int i = 0; i < n; ++i) {
        sort(a + i, a + n, greater<int>());
        for (int j = i + 1; j < n && a[i] > 0 && a[j] > 0; ++j) {
            --a[j];
            --a[i];
        }
        if (a[i] > 0)
            return false;
    }
    return true;
}

int main()
{
    while (cin >> n, n) {
        for (int i = 0; i < n; ++i)
            cin >> a[i];
        
        bool fail = false;
        int s = accumulate(a, a + n, 0);
        if (s % 2 || s > n*(n-1) || find_if(a, a + n, cmp(n)) != a + n)
            fail = true;
        if (fail || !solve())
            cout << "Not possible\n";
        else
            cout << "Possible\n";
    }
    return 0;
}
