#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdio>

/*
 * recur直接TLE，然后模拟2进制差点没有过。。。
 */

using namespace std;

struct habit_t {
	vector<int> likes, dislikes;

	habit_t() {};
	habit_t(const string& s) {
		likes.clear();
		dislikes.clear();
		for (int i = 0; i < s.size() - 1; ++i) {
			if (s[i] == '+')
				likes.push_back(s[++i] - 'A');
			else
				dislikes.push_back(s[++i] - 'A');
		}
	}
};

bool recipe[16];
habit_t friends[12];
int n;

bool judge()
{
	int i, j;

	for (i = 0; i < n; ++i) {
		bool ok = false;
		for (j = 0; j < friends[i].likes.size(); ++j)
			if (recipe[friends[i].likes[j]]) {
				ok = true;
				break;
			}
		if (ok)
			continue;

		for (j = 0; j < friends[i].dislikes.size(); ++j)
			if (!recipe[friends[i].dislikes[j]]) {
				ok = true;
				break;
			}
		if (!ok)
			break;
	}
	if (i != n)
		return false;
	return true;
}

bool select(int selection)
{
	int t = 16;
	bool* p = recipe;
	while (t > 0) {
		*p++ = (selection & 1);
		--t;
		selection >>= 1;
	}
	return judge();
}

int main()
{
	string s;

	while (cin >> s) {
		n = 0;
		do {
			friends[n++] = habit_t(s);
		} while (cin >> s, s != ".");

		bool have_solution = false;
		for (int selection = 0; selection <= (1 << 16) - 1; ++selection) {
			memset(recipe, 0, sizeof(recipe));
			if (select(selection)) {
				have_solution = true;
				break;
			}
		}
		if (!have_solution) {
			puts("No pizza can satisfy these requests.");
		} else {
			printf("Toppings: ");
			for (int j = 0; j < 16; ++j)
				if (recipe[j])
					putchar('A' + j);
			putchar('\n');
		}
	}
	return 0;
}
