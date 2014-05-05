#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <numeric>

using namespace std;

struct node_t {
	int v;
	node_t *left, *right;

	node_t(): left(0), right(0) {}
	node_t(int v, node_t* left, node_t* right) {
		this->v = v;
		this->left = left;
		this->right = right;
	}
};

struct cmp {
	bool operator()(node_t*& a, node_t*& b) {
		return a->v > b->v;
	}
};

int main()
{
	int N, v, s;
	while (cin >> N, N) {
		priority_queue<node_t*, vector<node_t*>, cmp> Q;
		for (int i = 0; i < N; ++i) {
			cin >> v;
			Q.push(new node_t(v, 0, 0));
		}
		while (Q.size() > 1) {
			node_t* a = Q.top(); Q.pop();
			node_t* b = Q.top(); Q.pop();
			Q.push(new node_t(a->v + b->v, a, b));
		}
		queue<node_t*> q;
		q.push(Q.top());
		s = 0;
		while (!q.empty()) {
			node_t* e = q.front(); q.pop();
			if (e->left && e->right) {
				s += e->v;
				q.push(e->left);
				q.push(e->right);
			}
		}
		cout << s << endl;
	}
	return 0;
}
