#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

#define player(x) ((x % 2) ? 2 : 1)
#define oppo(x) (3 - x)

int n;
char G[50][50];
set<string> vis;

bool try_to_insert()
{
	// rotate 0
	vector<string> s(4);
	for (int i = 0; i < n; ++i)
		s[0] += string(G[i], G[i] + n);
	if (!vis.insert(s[0]).second)
		return false;

	// rotate 90
	for (int j = n - 1; j >= 0; --j)
		for (int i = 0; i < n; ++i)
			s[1] += G[i][j];

	// rotate 180
	for (int i = n - 1; i >= 0; --i)
		for (int j = n - 1; j >= 0; --j)
			s[2] += G[i][j];

	// rotate -90
	for (int j = 0; j < n; ++j)
		for (int i = n - 1; i >= 0; --i)
			s[3] += G[i][j];

	sort(s.begin(), s.end());
	s.erase(unique(s.begin(), s.end()), s.end());
	for (int i = 0; i < s.size(); ++i)
		vis.insert(s[i]);
	return true;
}

int main()
{
	while (cin >> n, n) {
		memset(G, '0', sizeof(G));
		vis.clear();
		bool done = false;
		for (int i = 0; i < 2 * n; ++i) {
			int x, y;
			char ch;
			cin >> x >> y >> ch;
			G[x - 1][y - 1] = (ch == '+' ? '1' : '0');
			if (!done && !try_to_insert()) {
				done = true;
				printf("Player %d wins on move %d\n", oppo(player(i)), i + 1);
			}
		}
		if (!done)
			printf("Draw\n");
	}
	return 0;
}
