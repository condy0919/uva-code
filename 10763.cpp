#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

struct item {
	int location, target;

	item() {}
	item(int l, int t):location(l), target(t) {}

	bool operator==(const item& rh) const {
		return location == rh.location && target == rh.target;
	}

	bool operator<(const item& rh) const {
		if (location < rh.location)
			return true;
		if (location > rh.location)
			return false;
		if (target < rh.target)
			return true;
		return false;
	}
};

int main()
{
	int n;
	int x, y;
	while (cin >> n, n) {
		map<item, int> vis;
		for (int i = 0; i < n; ++i) {
			cin >> x >> y;
			++vis[item(x, y)];
			--vis[item(y, x)];
		}
		bool flag = true;
		for (const auto& i : vis)
			if (i.second != 0) {
				cout << "NO\n";
				flag = false;
				break;
			}
		if (flag)
			cout << "YES\n";
	}
	return 0;
}
