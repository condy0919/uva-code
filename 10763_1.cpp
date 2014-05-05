#include <iostream>
#include <algorithm>

using namespace std;

int a[500001], b[500001];
int n;

int main()
{
	while (cin >> n, n) {
		for (int i = 0; i < n; ++i)
			cin >> a[i] >> b[i];
		sort(a, a + n);
		sort(b, b + n);
		bool flag = true;
		for (int i = 0; i < n; ++i)
			if (a[i] != b[i]) {
				cout << "NO\n";
				flag = false;
				break;
			}
		if (flag)
			cout << "YES\n";
	}
	return 0;
}
