#include <iostream>
#include <algorithm>
#include <vector>

/*
 * 其实这题我不知道怎样判断平衡的。。。
 * 这种方法还是采用了从小的力矩开始向board上放。
 * 假设把某个箱子放在左边，若不平衡，必定是左边的力矩比右边的大。（否则，右边比左边大，就
 * 不会递归到此步了）。如果还要尝试此后的箱子，由于后面的箱子总是比以前放的箱子所带来的力矩大，
 * 则必然会引起不平衡。则可以在此处放弃，尝试另一边。
 */

using namespace std;

struct node_t {
	int pos, weight;

	node_t() {}
	node_t(int _p, int _w):pos(_p), weight(_w) {}

	bool operator<(const node_t& rh) const {
		return abs(pos) * weight < abs(rh.pos) * rh.weight;
	}
};

int length, weight, n;
vector<node_t> lp, rp, ans;

bool balance(int l, int r)
{
	int ls, rs;

	ls = rs = 0;
	for (int i = 0; i < l; ++i)
		ls += lp[i].weight * (-lp[i].pos * 2 - 3);
	for (int i = 0; i < r; ++i)
		rs += rp[i].weight * (rp[i].pos * 2 + 3);
	if (ls > rs + weight)
		return false;

	ls = rs = 0;
	for (int i = 0; i < l; ++i)
		ls += lp[i].weight * (-lp[i].pos * 2 + 3);
	for (int i = 0; i < r; ++i)
		rs += rp[i].weight * (rp[i].pos * 2 - 3);
	if (rs > ls + weight)
		return false;
	return true;
}

bool dfs(int l, int r)
{
	if (ans.size() == n)
		return true;

	if (l < lp.size()) {
		ans.push_back(lp[l]);
		if (balance(l + 1, r) && dfs(l + 1, r))
			return true;
		ans.pop_back();
	}

	if (r < rp.size()) {
		ans.push_back(rp[r]);
		if (balance(l, r + 1) && dfs(l, r + 1))
			return true;
		ans.pop_back();
	}

	return false;
}

int main()
{
	int round = 0;
	int pos, w;

	while (cin >> length >> weight >> n, length || weight || n) {
		lp.clear(); rp.clear(); ans.clear();
		weight *= 3;
		for (int i = 0; i < n; ++i) {
			cin >> pos >> w;
			vector<node_t>& ref = (pos < 0) ? lp : rp;
			ref.push_back(node_t(pos, w));
		}
		cout << "Case " << ++round << ':' << endl;

		sort(lp.begin(), lp.end());
		sort(rp.begin(), rp.end());
		if (dfs(0, 0))
			for (int i = ans.size() - 1; i >= 0; --i)
				cout << ans[i].pos << ' ' << ans[i].weight << endl;
		else
			cout << "Impossible" << endl;
	}
	return 0;
}
