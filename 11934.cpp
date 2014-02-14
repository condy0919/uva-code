#include <iostream>
#include <algorithm>

using namespace std;

#define fun(i) (a*i*i+b*i+c)

int main()
{
	int a, b, c, d, L;

	while (cin >> a >> b >> c >> d >> L, a||b||c||d||L) {
		int sum = 0;
		for (int i = 0; i <= L; ++i) {
			int f = fun(i);
			if (f % d == 0)
				++sum;
		}
		cout << sum << endl;
	}
	return 0;
}
