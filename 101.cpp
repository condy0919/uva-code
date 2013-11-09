#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> vec[25];
int n, a, b;
string cmd, pos;

void show_result()
{
	int i, j;
	for (i = 0; i < n; ++i) {
		cout << i << ":";
		for (j = 0; j < vec[i].size(); ++j)
			cout << " " << vec[i][j];
		cout << endl;
	}
}

char same_slot(int slot)
{
	char flag1 = 0, flag2 = 0;
	int j;

	for (j = 0; j < vec[slot].size(); ++j)
		if (vec[slot][j] == a)
			flag1 = 1;
		else if (vec[slot][j] == b)
			flag2 = 1;
	return flag1 & flag2;
}

int find_slot(int x)
{
	int i, j;
	for (i = 0; i < n; ++i)
		for (j = 0; j < vec[i].size(); ++j)
			if (vec[i][j] == x)
				return i;
	return -1;
}

int restore(int x)
{
	int pos = find_slot(x);
	int i;
	int ori;

	for (i = 0; i < vec[pos].size() && vec[pos][i] != x; ++i)
		;
	++i;
	while (i < vec[pos].size()) {
		ori = vec[pos][i];
		vec[ori].push_back(ori);
		vec[pos].erase(vec[pos].begin() + i);
	}
	return pos;
}

void move_to(int pos_a, int a, int pos_b)
{
	int i = vec[pos_a].size() - 1;
	vec[pos_b].push_back(vec[pos_a][i]);
	vec[pos_a].pop_back();
}

void move_upon(int pos_a, int a, int pos_b)
{
	int i;

	for (i = 0; i < vec[pos_a].size() && vec[pos_a][i] != a; ++i)
		;
	while (i < vec[pos_a].size()) {
		int up = vec[pos_a][i];
		vec[pos_b].push_back(up);
		vec[pos_a].erase(vec[pos_a].begin() + i);
	}
}

void move()
{
	int i;

	if (a == b)
		return;
	for (i = 0; i < n; ++i)
		if (same_slot(i))
			return;

	if (cmd == "move" && pos == "onto") {
		int pos_a = restore(a);
		int pos_b = restore(b);
		move_to(pos_a, a, pos_b);
	} else if (cmd == "move" && pos == "over") {
		int pos_a = restore(a);
		vec[pos_a].pop_back();
		int pos_b = find_slot(b);
		vec[pos_b].push_back(a);
	} else if (cmd == "pile" && pos == "onto") {
		int pos_b = restore(b);
		int pos_a = find_slot(a);
		move_upon(pos_a, a, pos_b);
	} else if (cmd == "pile" && pos == "over") {
		int pos_a = find_slot(a);
		int pos_b = find_slot(b);
		move_upon(pos_a, a, pos_b);
	}
}

int main()
{
	while (cin >> n) {
		for (int i = 0; i < n; ++i) {
			vec[i].clear();
			vec[i].push_back(i);
		}
		while (true) {
			cin >> cmd;
			if (cmd == "quit") {
				show_result();
				break;
			}
			cin >> a >> pos >> b;
			move();
		}
	}
	return 0;
}

