#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <cmath>

using namespace std;

string a[100];
int col_max;

bool calc(string a[], int n, int height, int row_limit)
{
	// if ok, set the col_max array
	// else just return false
	int i, j;
	int len=0;

	len = (col_max + 2)* (n/height);
	if (len > row_limit)
		return false;

	int m=0;
	if (n%height != 0)
		m = col_max;
	len+=m;
	if (len > row_limit)
		return false;
	return true;
}

int main()
{
	int n;

	while (cin >> n) {
		for (int i = 0; i < n; ++i)
			cin >> a[i];

		sort(a, a + n);
		int m=0;
		for (int i=0; i<n;++i)
			if (a[i].length()>m)
				m=a[i].length();
		col_max=m;
		// determine the col_max;

		// enumate the height, from 1 to n
		int col = 62/(col_max+2);
		int height = (n+col-2+1)/col;

		printf("------------------------------------------------------------\n");
		int cnt=0;
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < col && j*height+i < n; ++j) {
				cout << a[j*height+i];
				if(cnt==n-1&&j<col-1)
					;
				else
					printf("%*c", col_max-a[j*height+i].length()+2, ' ');
				++cnt;
			}
			putchar('\n');
		}
	}
	return 0;
}

