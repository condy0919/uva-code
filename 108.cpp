#include <iostream>
#include <algorithm>

/*
 * 原来是max sequence的变形，竟然没有看出来，惭愧.
 */

using namespace std;

int a[101][101];
int N;

int main()
{
	int _max = -1270001;

	cin >> N;
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j) {
			cin >> a[i][j];
			_max = max(_max, a[i][j]);
		}

	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j)
			a[i][j] += a[i][j - 1];
	for (int j = 1; j <= N; ++j)
		for (int i = 1; i <= N; ++i)
			a[i][j] += a[i - 1][j];

	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j)
			for (int i1 = 0; i1 < i; ++i1)
				for (int i2 = 0; i2 < j; ++i2)
					_max = max(_max, a[i][j] 
							- a[i1][j] - a[i][i2] + a[i1][i2]);
	cout << _max << endl;
	return 0;
}
