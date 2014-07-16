#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

/*
 * 一开始没有想到这种方法，或者说直接想到了DAG，可惜输出一直错了。
 */

struct elem_t {
	int w, s, id;
	elem_t(int _w = 0, int _s = 0, int _id = 0):w(_w), s(_s), id(_id) {}
};

bool cmp(const elem_t& lhs, const elem_t& rhs) {
	if (lhs.w == rhs.w)
		return lhs.s > rhs.s;
	return lhs.w < rhs.w;
}

vector<elem_t> vec;
int parent[1001], f[1001];

void print_ans(int i) {
	stack<int> S;
	while (i != -1) {
		S.push(vec[i].id);
		i = parent[i];
	}
	cout << S.size() << endl;
	while (!S.empty()) {
		cout << S.top() << endl;
		S.pop();
	}
}

int main() {
	int id = 0, w, s;
	while (cin >> w >> s)
		vec.push_back(elem_t(w, s, ++id));
	sort(vec.begin(), vec.end(), cmp);

	fill(parent, parent + id, -1);
	fill(f, f + id, 1);

	// start dp
	for (int i = 0; i < vec.size(); ++i)
		for (int j = 0; j < i; ++j)
			if (vec[i].s < vec[j].s && f[i] < f[j] + 1) {
				f[i] = f[j] + 1;
				parent[i] = j;
			}
	print_ans(max_element(f, f + vec.size()) - f);
	return 0;
}
