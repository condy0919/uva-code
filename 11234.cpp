#include <iostream>
#include <stack>
#include <string>
#include <queue>
#include <cctype>

using namespace std;

struct node_t {
	char ch;
	struct node_t* left;
	struct node_t* right;
};

void build(node_t*& node, const string& str)
{
	if (str.length() == 0)
		return;

	int num_operator = 0, num_operand = 0;
	int i = str.length() - 1;
	int j;
	node = new node_t;
	node->left = node->right = 0;
	node->ch = str[i];

	for (j = i - 1; j >= 0 && num_operator != num_operand - 1; --j) {
		if (isupper(str[j]))
			++num_operator;
		else
			++num_operand;
	}
	build(node->left, str.substr(0, j + 1));
	build(node->right, str.substr(j + 1, i - j - 1));
}

void print(const node_t* node)
{
	queue<const node_t*> Q;
	stack<char> S;

	Q.push(node);
	while (!Q.empty()) {
		const node_t* e = Q.front();
		Q.pop();
		S.push(e->ch);
		if (e->left)
			Q.push(e->left);
		if (e->right)
			Q.push(e->right);
	}
	while (!S.empty()) {
		cout << S.top();
		S.pop();
	}
}

void destroy(const node_t* node)
{
	if (node) {
		destroy(node->left);
		destroy(node->right);
		delete node;
	}
}

int main()
{
	int n;
	string exp;

	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> exp;
		node_t* root = 0;
		build(root, exp);
		print(root);
		cout << endl;
		destroy(root);
	}
	return 0;
}
