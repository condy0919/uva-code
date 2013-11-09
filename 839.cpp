#include <iostream>

using namespace std;

struct node_t {
	int weight;
	int left_dis, right_dis;

	struct node_t* left;
	struct node_t* right;

	node_t() { left = right = 0; left_dis = right_dis = 0; }
};

void build(node_t*& node)
{
	int wl, dl, wr, dr;

	cin >> wl >> dl >> wr >> dr;

	node = new node_t;
	node->left_dis = dl;
	node->right_dis = dr;
	
	if (wl == 0) {
		build(node->left);
	} else {
		node->left = new node_t;
		node->left->weight = wl;
	}
	if (wr == 0) {
		build(node->right);
	} else {
		node->right = new node_t;
		node->right->weight = wr;
	}
}

void destroy(node_t* node)
{
	if (node) {
		destroy(node->left);
		destroy(node->right);
		delete node;
	}
}

bool balance(node_t* node, int& weight)
{
	if (!node) {
		weight = 0;
		return true;
	}
	int w1, w2;
	if (!balance(node->left, w1))
		return false;
	if (!balance(node->right, w2))
		return false;

	if (node->left && node->right) {
		if (w1 * node->left_dis == w2 * node->right_dis) {
			weight = w1 + w2;
			return true;
		}
		return false;
	}
	weight = node->weight;
	return true;
}

int main()
{
	int cases, temp;

	cin >> cases;
	while (cases-- > 0) {
		node_t* root = 0;
		build(root);
		if (balance(root, temp))
			cout << "YES\n";
		else
			cout << "NO\n";
		if (cases)
			cout << endl;
		destroy(root);
	}
	return 0;
}
