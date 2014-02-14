#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

/*
 * 下次做这题的时候再换种方法。由于数据量很小，可以直接DFS。
 */

struct volunteer_t {
	int suit[2];
};

int cloth[6];
volunteer_t volunteer[30];
int M, N;

int convert(const string& s)
{
	if (s == "L")
		return 0;
	if (s == "XL")
		return 1;
	if (s == "XXL")
		return 2;
	if (s == "S")
		return 3;
	if (s == "XS")
		return 4;
	return 5;
}

bool dfs(int cur)
{
	if (cur == M)
		return true;

	if (cloth[volunteer[cur].suit[0]] > 0) {
		--cloth[volunteer[cur].suit[0]];
		if (dfs(cur + 1))
			return true;
		++cloth[volunteer[cur].suit[0]];
	}

	if (cloth[volunteer[cur].suit[1]] > 0) {
		--cloth[volunteer[cur].suit[1]];
		if (dfs(cur + 1))
			return true;
		++cloth[volunteer[cur].suit[1]];
	}

	return false;
}

int main()
{
	int total_test;
	string suit1, suit2;

	cin >> total_test;
	while (total_test-- > 0) {
		cin >> N >> M;
		memset(volunteer, 0, sizeof(volunteer));
		fill(cloth, cloth + 6, N / 6);
		for (int i = 0; i < M; ++i) {
			cin >> suit1 >> suit2;
			volunteer[i].suit[0] = convert(suit1);
			volunteer[i].suit[1] = convert(suit2);
		}
		if (dfs(0))
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	return 0;
}
