#include <iostream>
#include <algorithm>
using namespace std;
/*
 * ab.... -> fine = t[a] * f[b] + ....
 * ba.... -> find = t[b] * f[a] + ....
 *
 * t[a] * f[b] < t[b] * f[a] ==> t[a] / f[a] < t[b] / f[b]
 */
struct task {
	int time, fine;
	int no;
} a[1000];
bool cmp(const task& a, const task& b)
{
	return (double)a.time / a.fine < (double)b.time / b.fine;
}
int main()
{
	int T, N;
	cin >> T;
	while (T-- > 0) {
		cin >> N;
		for (int i = 0; i < N; ++i) {
			cin >> a[i].time >> a[i].fine;
			a[i].no = i + 1;
		}
		stable_sort(a, a + N, cmp);
		cout << a[0].no;
		for (int i = 1; i < N; ++i)
			cout << " " << a[i].no;
		cout << endl;
		if (T)
			cout << endl;
	}
	return 0;
}
