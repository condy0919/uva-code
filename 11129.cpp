#include <iostream>
#include <algorithm>
using namespace std;
#define N 10005
int n;
int a[N], b[N];
struct c_unique {
    int current;
    c_unique():current(0){}
    int operator()() { return current++; }
} unique_number;
void solve(int beg, int end) {
    int t;
    if (beg + 2 >= end) // beg x end , just 2 elements
        return;
    copy(a + beg, a + end, b);
    int j = beg;
    for (int i = 0; i < end - beg; i += 2)
        a[j++] = b[i];
    t = j;
    for (int i = 1; i < end - beg; i += 2)
        a[j++] = b[i];
    solve(beg, t);
    solve(t, end);
}
int main() {
    while (cin >> n, n > 0) {
        generate(a, a + n, unique_number);
        cout << n << ":";
        solve(0, n);
        for_each(a, a + n, [](int x){cout << " " << x;});
        cout << endl;
    }
    return 0;
}
