#include <cstdio>
#include <cctype>

/*
 * 又犯了细节上的错误，数可能为负，悲剧的我没有考虑负号。。。
 */

using namespace std;

struct node_t {
	int v;
	struct node_t* left;
	struct node_t* right;

	node_t() { left = right = 0; }
};

int stack[4];
int sp;

void unget(int ch)
{
	stack[sp++] = ch;
}

int getch()
{
	return (sp > 0) ? stack[--sp] : getchar();
}

void whitespace()
{
	int ch;

	while (isspace(ch = getch()))
		;
	unget(ch);
}

void build(node_t*& node)
{
	int ch, v = 0;
	bool negative = false;

	whitespace();
	getch();// '('
	whitespace();
	ch = getch();
	if (ch == ')')
		return;
	if (ch == '-') {
		negative = true;
		ch = getch();
	}
	v = ch - '0';
	while (isdigit(ch = getch()))
		v = 10 * v + (ch - '0');
	v = negative ? -v : v;
	unget(ch);

	node = new node_t;
	node->v = v;
	build(node->left);
	build(node->right);
	whitespace();
	getch();// ')'
}

void destroy(node_t* node)
{
	if (node) {
		destroy(node->left);
		destroy(node->right);
		delete node;
	}
}

bool solve(node_t* node, int cost, int goal)
{
	if (node) {
		if (!node->left && !node->right && cost + node->v == goal)
			return true;
		cost += node->v;
		if (solve(node->left, cost, goal))
			return true;
		if (solve(node->right, cost, goal))
			return true;
	}
	return false;
}

int main()
{
	int n;
	node_t* root;

	while (scanf("%d", &n) == 1) {
		root = 0;
		build(root);
		if (solve(root, 0, n))
			puts("yes");
		else
			puts("no");

		destroy(root);
	}
	return 0;
}

