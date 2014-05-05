#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	int T;
	int l, n;
	int p;
	cin >> T;
	while (T-- > 0) {
		cin >> l >> n;
		vector<int> vec;
		for (int i = 0; i < n; ++i) {
			cin >> p;
			vec.push_back(p);
		}
		int earliest, latest;
		if (vec[0] > l / 2) {
			earliest = l - vec[0];
			latest = vec[0];
		} else {
			earliest = vec[0];
			latest = l - vec[0];
		}
		for (int i = 1; i < n; ++i) {
			if (vec[i] > l / 2) {
				earliest = max(earliest, l - vec[i]);
				latest = max(latest, vec[i]);
			} else {
				earliest = max(earliest, vec[i]);
				latest = max(latest, l - vec[i]);
			}
		}
		cout << earliest << " " << latest << endl;
	}
	return 0;
}
