#include <iostream>
#include <algorithm>

/*
 * C++的版本写起来好简单啊。。
 */

using namespace std;

int main()
{
	int T;
	int N, H;
	bool vis[16];
	int i;

	cin >> T;
	while (T-- > 0) {
		cin >> N >> H;
		for (i = 0; i < N - H; ++i)
			vis[i] = false;
		for (; i < N; ++i)
			vis[i] = true;
		do {
			for (int i = 0; i < N; ++i)
				cout << (int)vis[i];
			cout << endl;
		} while (next_permutation(vis, vis + N));
		if (T)
			cout << endl;
	}
	return 0;
}
