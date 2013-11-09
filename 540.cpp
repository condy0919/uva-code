#include <iostream>
#include <list>
#include <string>
#include <cstring>

using namespace std;

/*
 * 一开始不熟悉list的用法，各种错啊。。。
 * 何况英文意思搞不懂啊。。。
 */

int ref[1000000];
list<int> L;
list<int>::iterator rightest_pos[1000];
int cnt[1000];

void init()
{
	memset(cnt, 0, sizeof(cnt));
	L.clear();
	for (int i = 0; i < 1000; ++i)
		rightest_pos[i] = L.end();
}

void dequeue()
{
	int e = L.front();
	cout << e << endl;
	--cnt[ref[e]];
	L.pop_front();
	if (cnt[ref[e]] == 0)
		rightest_pos[ref[e]] = L.end();
}

void enqueue(int x)
{
	int team_id = ref[x];

	++cnt[team_id];
	if (rightest_pos[team_id] == L.end()) {
		L.push_back(x);
		rightest_pos[team_id] = L.end();
		--rightest_pos[team_id];
		return;
	}

	list<int>::iterator loc = rightest_pos[team_id];
	++loc;
	L.insert(loc, x);
	rightest_pos[team_id] = --loc;
}


int main()
{
	int k = 0, t, n, x;

	while (cin >> t, t) {
		for (int i = 0; i < t; ++i) {
			cin >> n;
			while (n-- > 0) {
				cin >> x;
				ref[x] = i;
			}
		}
		cout << "Scenario #" << ++k << endl;
		init();
		string str;
		while (cin >> str, str != "STOP") {
			if (str == "DEQUEUE") {
				dequeue();
			} else {
				cin >> x;
				enqueue(x);
			}
		}
		cout << endl;
	}
	return 0;
}

