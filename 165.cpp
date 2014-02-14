#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

/*
 * 最近思路各种乱，连这种简单题都不会了。。。
 * http://www.cnblogs.com/staginner/archive/2011/09/06/2168900.html
 */

using namespace std;

int h, k;
vector<int> type_ans;
int _max;

bool check(int goal, int cur, int num, int sum, const vector<int>& type)
{
	if (sum == goal)
		return true;
	if (cur == type.size() || num == h)// type limitation or total selection run out
		return false;

	if (check(goal, cur + 1, num, sum, type))
		return true;
	if (check(goal, cur, num + 1, sum + type[cur], type))
		return true;
	return false;
}

void dfs(int cur_max, vector<int>& type)
{
	if (cur_max - 1 > _max) {
		_max = cur_max - 1;
		type_ans = type;
	}

	if (check(cur_max, 0, 0, 0, type))
		dfs(cur_max + 1, type);
	if (type.size() < k) {
		type.push_back(cur_max);
		dfs(cur_max + 1, type);
		type.pop_back();
	}
}

int main()
{
	vector<int> type;
	while (cin >> h >> k, h || k) {
		_max = 0;
		type_ans.clear();
		type.clear();
		dfs(1, type);
		for (int i = 0; i < type_ans.size(); ++i)
			printf("%3d", type_ans[i]);
		printf(" ->%3d\n", _max);
	}
	return 0;
}
