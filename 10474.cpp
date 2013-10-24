#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <numeric>

using namespace std;

int cnt[10000];

int main()
{
	int n, q;
	int round = 0;
	int x;

	while (cin >> n >> q) {
		if (n == 0 && q == 0)
			break;

		cout << "CASE# " << ++round << ":" << endl;
		memset(cnt, 0, sizeof(cnt));

		while (n-- > 0) {
			cin >> x;
			cnt[x]++;
		}

		for (int i = 0; i < q; ++i) {
			cin >> x;
			int pos;

			if (cnt[x] == 0)
				cout << x << " not found" << endl;
			else {
				pos = accumulate(cnt, cnt + x, 0) + 1;
				cout << x << " found at " << pos << endl;
			}
		}
	}

	return 0;
}
