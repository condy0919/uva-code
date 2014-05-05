#include <iostream>
#include <algorithm>

using namespace std;

/*
 * 一个绝对值不等式...
 */

struct pred {
	int lo, hi;
	pred(int lo, int hi) {
		this->lo = lo;
		this->hi = hi;
	}
	bool operator()(int x) {
		return x >= lo && x <= hi;
	}
};

int a[1000000];
int main()
{
	int n;
	while (cin >> n) {
		for (int i = 0; i < n; ++i)
			cin >> a[i];
		sort(a, a + n);
		int lo, hi;
		if (n % 2 == 0)
			lo = a[n/2 - 1], hi = a[n/2];
		else
			lo = hi = a[n/2];
		int c = count_if(a, a + n, pred(lo, hi));
		cout << lo << " " << c << " " << hi - lo + 1 << endl;
	}
	return 0;
}
