#include <iostream>
#include <algorithm>

using namespace std;

const char op[4] = "+-*";
int n[5];
bool vis[5];

int calc(int a, char op, int b)
{
	if (op == '+')
		return a + b;
	if (op == '-')
		return a - b;
	return a * b;
}

bool dfs(int v, int m)
{
	if (m == 5)
		return v == 23;

	for (int i = 0; i < 3; ++i) {
		int t = calc(v, op[i], n[m]);
		if (dfs(t, m + 1))
			return true;
	}
	return false;
}

int main()
{
	while (true) {
		for (int i = 0; i < 5; ++i)
			cin >> n[i];

		if (n[0] == 0 && n[1] == 0 && n[2] == 0 && 
				n[3] == 0 && n[4] == 0)
			break;

		bool possible = false;
		sort(n, n + 5);
		do {

			if (dfs(n[0], 1)) {
				possible = true;
				break;
			}
		} while (next_permutation(n, n + 5));
		if (possible)
			cout << "Possible\n";
		else
			cout << "Impossible\n";
	}
	return 0;
}
