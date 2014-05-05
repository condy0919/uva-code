#include <iostream>
#include <cstdio>
#include <algorithm>
#include <limits>


using namespace std;

int n, m;
int a[1000];

int calc(int query)
{
	int diff = numeric_limits<int>::max();
	int ans;

	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
			if (abs(query - a[i] - a[j]) < diff) {
				diff = abs(query - a[i] - a[j]);
				ans = a[i] + a[j];
			}
	return ans;
}

int main()
{
	int t = 0;

	while (cin >> n, n) {
		for (int i = 0; i < n; ++i)
			cin >> a[i];
		cin >> m;
		printf("Case %d:\n", ++t);

		for (int i = 0; i < m; ++i) {
			int query;
			cin >> query;
			printf("Closest sum to %d is %d.\n", query, calc(query));
		}
	}

	return 0;
}
