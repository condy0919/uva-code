#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

#define N 200

struct node_t {
	int v;

	struct node_t* left;
	struct node_t* right;

	node_t() { left = right = 0; }
};

bool build(node_t*& node)
{
	extern bool first;
	int v;
	cin >> v;

	if (first) {
		if (v == -1)
			return false;
		first = false;
	}
	if (v > 0) {
		node = new node_t;
		node->v = v;
		build(node->left);
		build(node->right);
	}
	return true;
}

void destroy(node_t* node)
{
	if (node) {
		destroy(node->left);
		destroy(node->right);
		delete node;
	}
}

void travel(node_t* node, int pos)
{
	extern int leaves[];

	if (node) {
		leaves[pos] += node->v;
		travel(node->left, pos - 1);
		travel(node->right, pos + 1);
	}
}

void show_leaves()
{
	extern int leaves[];
	extern int round;

	bool first_elem = true;
	cout << "Case " << ++round << ":" << endl;;
	for (int i = 0; i < N; ++i) {
		if (leaves[i] == 0)
			continue;
		if (first_elem) {
			cout << leaves[i];
			first_elem = false;
		} else
			cout << " " << leaves[i];
	}
	cout << endl << endl;
}

bool first = true;
int leaves[N];
int round;

int main()
{
	node_t* root = 0;
	while (build(root)) {
		travel(root, N/2);
		show_leaves();
		destroy(root);
		root = 0;
		first = true;
		memset(leaves, 0, sizeof(leaves));
	}
	return 0;
}

