#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

enum type_t {
	PARENT, CHILD 
};

#define BLACK true
#define WHITE false

struct node_t {
	type_t type;
	bool color;
	struct node_t* next[4];

	node_t() { next[0]=next[1]=next[2]=next[3]=0; color = WHITE; }
};

void build(node_t*& node)
{
	int ch = getchar();
	if (ch == '\n')
		return;

	node = new node_t;
	if (ch == 'p') {
		node->type = PARENT;
		for (int i = 0; i < 4; ++i)
			build(node->next[i]);
	} else {
		node->type = CHILD;
		node->color = (ch == 'e') ? WHITE : BLACK;
	}
}

void add(node_t*& s, node_t* a, node_t* b)
{
	if (!a && !b)
		return;

	s = new node_t;
	if (a && b) {
		if (a->color == BLACK || b->color == BLACK) {
			s->color = BLACK;
			s->type = CHILD;
		} else if (a->type == PARENT || b->type == PARENT) {
			s->type = PARENT;
			for (int i = 0; i < 4; ++i)
				add(s->next[i], a->next[i], b->next[i]);
		}
	} else if (!a && b) {
		s->type = b->type;
		if (b->type == PARENT) {
			for (int i = 0; i < 4; ++i)
				add(s->next[i], 0, b->next[i]);
		} else {
			s->color = b->color;
		}
	} else if (a && !b) {
		s->type = a->type;
		if (a->type == PARENT) {
			for (int i = 0; i < 4; ++i)
				add(s->next[i], a->next[i], 0);
		} else {
			s->color = a->color;
		}
	}
}

int calc(node_t* node, int pixels)
{
	int ret = 0;

	if (!node)
		return 0;
	if (node->type == PARENT) {
		for (int i = 0; i < 4; ++i)
			ret += calc(node->next[i], pixels / 2);
	} else if (node->color == BLACK) {
		ret += pixels*pixels;
	}
	return ret;
}

void destroy(node_t* node)
{
	if (node) {
		if (node->type == PARENT)
			for (int i = 0; i < 4; ++i)
				destroy(node->next[i]);
		delete node;
	}
}

int main()
{
	int total_test;
	node_t *t1, *t2, *t3;
	cin >> total_test;
	getchar();
	while (total_test-- > 0) {
		t1 = t2 = t3 = 0;
		build(t1);
		getchar();
		build(t2);
		getchar();
		add(t3, t1, t2);
		cout << "There are " << calc(t3, 32) << " black pixels." << endl;
		destroy(t1);
		destroy(t2);
		destroy(t3);
	}
	return 0;
}

