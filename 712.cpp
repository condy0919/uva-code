#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstdio>

using namespace std;

int n, m;

char calc(string& x, const vector<string>& ref, const string& bottom)
{
	int pos = 1;
	int i;

	for (i = 0; i < ref.size(); ++i) {
		int p = atoi(ref[i].c_str() + 1);
		if (x[p - 1] == '1')
			pos = 2 * pos + 1;
		else
			pos = 2 * pos;
	}
	return bottom[pos - (1 << n)];
}

int main()
{
	string bottom;
	string var, x;
	vector<string> order;
	int round = 0;

	while (cin >> n, n) {
		order.resize(n);
		for (int i = 0; i < n; ++i) {
			cin >> var;
			order[i] = var;
		}
		cout << "S-Tree #" << ++round << ":" << endl;
		cin >> bottom;
		cin >> m;
		for (int i = 0; i < m; ++i) {
			cin >> x;
			char ans = calc(x, order, bottom);
			putchar(ans);
		}
		putchar('\n');
		putchar('\n');
	}

	return 0;
}
