#include <iostream>
#include <algorithm>
#include <cstring>

/*
 * 这道一开始连意思都没有读懂。结合着图看，仍旧不懂。
 */

using namespace std;

struct ticket_t {
	int start, end, passanger;
};

int limit, n, tickets;
int cnt[8];
ticket_t ticket[27];
int ans;

void dfs(int cur, int price)
{
	ans = max(ans, price);
	for (int i = cur; i < tickets; ++i) {
		bool overflow = false;
		for (int j = ticket[i].start + 1; j <= ticket[i].end; ++j) {
			cnt[j] += ticket[i].passanger;
			if (cnt[j] > limit)
				overflow = true;
		}
		if (!overflow)
			dfs(i + 1, ticket[i].passanger * (ticket[i].end - ticket[i].start) + price);
		for (int j = ticket[i].start + 1; j <= ticket[i].end; ++j)
			cnt[j] -= ticket[i].passanger;
	}
}

int main()
{
	while (cin >> limit >> n >> tickets, limit || n || tickets) {
		ans = 0;
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < tickets; ++i)
			cin >> ticket[i].start >> ticket[i].end >> ticket[i].passanger;
		dfs(0, 0);
		cout << ans << endl;
	}
	return 0;
}
