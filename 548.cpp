#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

struct node_t {
	int v;
	
	struct node_t* left;
	struct node_t* right;
	
	node_t() { left = right = 0; }
};

void repair(node_t*& node, const vector<int>& in, const vector<int>& post)
{
	if (in.empty())
		return;
	int middle = post.back();
	int i;

	node = new node_t;
	node->v = middle;

	for (i = 0; i < in.size(); ++i)
		if (middle == in[i])
			break;
	repair(node->left, vector<int>(in.begin(), in.begin() + i), vector<int>(post.begin(), post.begin() + i));
	repair(node->right, vector<int>(in.begin() + i + 1, in.end()), vector<int>(post.begin() + i, post.begin() + post.size() - 1));
}

void destroy(node_t* node)
{
	if (node) {
		destroy(node->left);
		destroy(node->right);
		delete node;
	}
}


int min_cost_path;
int leaf_val;
void solve(node_t* root, int cost)
{
	if (root) {
		solve(root->left, cost + root->v);
		solve(root->right, cost + root->v);
		if (!root->left && !root->right && cost + root->v < min_cost_path) {
			min_cost_path = cost + root->v;
			leaf_val = root->v;
		}
	}
}

int main()
{
	string inorder, postorder;
	int x;

	while (getline(cin, inorder) && getline(cin, postorder)) {
		istringstream in(inorder), post(postorder);
		vector<int> in_order, post_order;
		while (in >> x)
			in_order.push_back(x);
		while (post >> x)
			post_order.push_back(x);

		node_t* root = 0;
		repair(root, in_order, post_order);
		min_cost_path = 0x7fffffff;
		solve(root, 0);
		cout << leaf_val << endl;
		destroy(root);
	}
	return 0;
}

