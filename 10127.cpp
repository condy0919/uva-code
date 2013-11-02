#include <iostream>

using namespace std;

int main()
{
	int n, ans, cnt;

	while (cin >> n) {
		ans = cnt = 0;
		do {
			ans = (10 * ans + 1) % n;
			++cnt;
		} while (ans != 0);
		cout << cnt << endl;
	}
	return 0;
}

