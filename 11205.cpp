#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

int v[100];
int P, N;
bool cnt[1 << 15];

bool check(int mask)
{
	int i;
	
	memset(cnt, 0, sizeof(cnt));
	for (i = 0; i < N; ++i)
		if (!cnt[v[i] & mask])
			cnt[v[i] & mask] = true;
		else 
			return false;
	return true;
}

bool dfs(int mask, int pos, int t)
{
	bool ret;

	if (P - pos < t)
		return false;
	if (t == 0)
		return check(mask);

	if (dfs(mask | (1 << pos), pos + 1, t - 1))
		return true;

	if (dfs(mask, pos + 1, t))
		return true;
}

int main()
{
	int T;

	scanf("%d", &T);
	while (T-- > 0) {
		scanf("%d%d", &P, &N);

		for (int i = 0; i < N; ++i) {
			int s = 0, c;
			for (int j = 0; j < P; ++j) {
				scanf("%d", &c);
				s = 2 * s + c;
			}
			v[i] = s;
		}
		int i;
		for (i = 0; i <= P; ++i)
			if (dfs(0, 0, i))
				break;
		printf("%d\n", i);
	}
	return 0;
}
