#include <iostream>
#include <algorithm>
#include <limits>
#include <cstring>

using namespace std;

#define SIZE 500501

struct item {
	int a, b;
	int sum;
	item* next;
	
	item(int _i, int _j, int _sum):a(_i),b(_j),sum(_sum),next(0) {}
	item():next(0) {}
};
int a[1001], n;
item* head[SIZE];

int hash(int s)
{
	return (s & 0x7fffffff) % SIZE;
}

void insert(int i, int j)
{
	int h = hash(a[i] + a[j]);
	item* newone = new item(i, j, a[i] + a[j]);
	newone->next = head[h];
	head[h] = newone;
}

bool unique(int a, int b, int c, int d)
{
	if (a == c || a == d)
		return false;
	if (b == c || b == d)
		return false;
	return true;
}

void destroy()
{
	item *u, *next;;
	for (int i = 0; i < SIZE; ++i) {
		u = head[i];
		while (u) {
			next = u->next;
			delete u;
			u = next;
		}
	}
}

int main()
{
	while (cin >> n, n) {
		for (int i = 0; i < n; ++i)
			cin >> a[i];
		memset(head, 0, sizeof(head));
		for (int i = 0; i < n; ++i)
			for (int j = i + 1; j < n; ++j)
				insert(i, j);
		int _max = numeric_limits<int>::min();
		for (int c = 0; c < n; ++c)
			for (int d = 0; d < n; ++d) {
				if (c == d)
					continue;
				int h = hash(a[d] - a[c]);
				for (item* i = head[h]; i; i = i->next) {
					if (i->sum == a[d] - a[c] && unique(i->a, i->b, c, d))
						_max = max(_max, a[d]);
				}
			}
		if (_max == numeric_limits<int>::min())
			cout << "no solution" << endl;
		else
			cout << _max << endl;
		destroy();
	}
	return 0;
}
