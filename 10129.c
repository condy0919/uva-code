#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * 这道题一开始用DFS做一直不对，后来改用Union-Find set就AC了..
 */

int N, T;
char str[1002];
int in[26], out[26];
int p[26];

int find(int x)
{
	if (x == p[x])
		return x;
	return p[x] = find(p[x]);
}

int main()
{
	int i;
	int k1, k2;
	int root;
	int ans, id, od;

	scanf("%d", &T);
	while (T-- > 0) {
		scanf("%d", &N);
		memset(in, 0, sizeof(in));
		memset(out, 0, sizeof(out));
		ans = od = id = 0;

		for (i = 0; i < 26; ++i)
			p[i] = i;
		for (i = 0; i < N; ++i) {
			scanf("%s", str);
			k1 = str[0] - 'a';
			k2 = str[strlen(str) - 1] - 'a';
			++in[k2];
			++out[k1];
			root = p[find(k1)] = find(k2);
		}

		for (i = 0; i < 26; ++i) {
			if (in[i] == 0 && out[i] == 0)
				continue;
			if (find(p[i]) != root)
				++ans;
			if (in[i] - out[i] == 1)
				++id;
			else if (in[i] - out[i] == -1)
				++od;
			else if (abs(in[i] - out[i]) > 1)
				break;
		}
		if (i < 26 || ans > 0 || id > 1 || od > 1)
			printf("The door cannot be opened.\n");
		else
			printf("Ordering is possible.\n");

	}
	return 0;
}
