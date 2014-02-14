#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
#include <sstream>

/*
 * 一开始字母打错了。。。果然细心是永恒的主题。。。
 */

using namespace std;

const char* __color = "CDHS";
const char* __point = " A23456789TJQK";
const char* level[9] = {
	"highest-card", "one-pair", "two-pairs", "three-of-a-kind", "straight", "flush", "full-house", "four-of-a-kind", "straight-flush"
};

struct card_t {
	int color, point;

	card_t() { color = point = 0; }

	card_t(char* s) {
		int i;

		for (i = 0; s[1] != __color[i]; ++i) ;
		color = i;
		for (i = 1; s[0] != __point[i]; ++i) ;
		point = i;
	}
};

bool straight_flush(card_t hand[])
{
	int i;
	int a[5];

	for (i = 0; i < 5; ++i)
		if (hand[i].color != hand[0].color)
			return false;
	for (i = 0; i < 5; ++i)
		a[i] = hand[i].point;
	sort(a, a + 5);
	for (i = 0; i < 5 - 1 && a[i] == a[i + 1] - 1; ++i) ;

	if (i == 4)
		return true;
	if (a[0] == 1 && a[4] == 13)
		return true;
	return false;
}

bool four_of_a_kind(card_t hand[])
{
	int cnt[14] = {0};
	int i;

	for (i = 0; i < 5; ++i)
		if (++cnt[hand[i].point] == 4)
			return true;
	return false;
}

bool full_house(card_t hand[])
{
	int cnt[14] = {0};
	bool flag3 = false, flag2 = false;
	int i;

	for (i = 0; i < 5; ++i)
		++cnt[hand[i].point];
	for (i = 0; i < 5; ++i)
		if (cnt[hand[i].point] == 3)
			flag3 = true;
		else if (cnt[hand[i].point] == 2)
			flag2 = true;
	return flag3 && flag2;
}

bool flush(card_t hand[])
{
	int i;

	for (i = 0; i < 5; ++i)
		if (hand[i].color != hand[0].color)
			return false;
	return true;
}

bool straight(card_t hand[])
{
	int a[5], i;

	for (i = 0; i < 5; ++i)
		a[i] = hand[i].point;
	sort(a, a + 5);
	
	for (i = 0; i < 5 - 1 && a[i] == a[i + 1] - 1; ++i) ;

	if (i == 4)
		return true;
	if (a[0] == 1 && a[1] == 10 && a[2] == 11 && a[3] == 12 && a[4] == 13)
		return true;
	return false;
}

bool three_of_a_kind(card_t hand[])
{
	int cnt[14] = {0};
	int i;
	bool flag = false, flag_1 = false, flag_2 = false;

	for (i = 0; i < 5; ++i)
		++cnt[hand[i].point];
	for (i = 1; i < 14; ++i) {
		if (cnt[i] == 3)
			flag = true;
		if (cnt[i] == 1) {
			if (!flag_1)
				flag_1 = true;
			else
				flag_2 = true;
		}
	}
	return flag && flag_1 && flag_2;
}

bool two_pairs(card_t hand[])
{
	int cnt[14] = {0};
	int i;
	bool flag_1 = false, flag_2 = false, flag_3 = false;

	for (i = 0; i < 5; ++i)
		++cnt[hand[i].point];
	for (i = 1; i < 14; ++i)
		if (cnt[i] == 2) {
			if (!flag_1)
				flag_1 = true;
			else
				flag_2 = true;
		} else if (cnt[i] == 1)
			flag_3 = true;
	return flag_1 && flag_2 && flag_3;
}

bool one_pair(card_t hand[])
{
	bool vis[14] = {false};
	int cnt[14] = {0};
	int i;

	for (i = 0; i < 5; ++i) {
		++cnt[hand[i].point];
		vis[hand[i].point] = true;
	}
	for (i = 1; i < 14; ++i)
		if (cnt[i] == 2)
			return accumulate(vis,  vis + 14, 0) == 4;
	return false;
}

bool high_card(card_t hand[])
{
	return true;
}

int estimate(card_t hand[])
{
	bool (*est[9])(card_t*) = {
		straight_flush, four_of_a_kind, full_house, flush, straight, three_of_a_kind, two_pairs, one_pair, high_card
	};

	for (int i = 0; i < 9; ++i)
		if (est[i](hand))
			return 9 - 1 - i;
}

void exchange(card_t hand[], card_t deck[], int i, int n, int& _max)
{
	if (n == 0) {
		// estimate the value
		_max = max(_max, estimate(hand));
		return;
	}
	if (4 - i + 1 < n)
		return;

	// exchange
	swap(hand[i], deck[n - 1]);
	exchange(hand, deck, i + 1, n - 1, _max);
	swap(hand[i], deck[n - 1]);
	
	// no exchange
	exchange(hand, deck, i + 1, n, _max);
}

int solve(card_t hand[], card_t deck[])
{
	int _max = 0;
	int n;

	for (n = 0; n <= 5; ++n)
		exchange(hand, deck, 0, n, _max);
	return _max;
}

int main()
{
	string s;
	int i;
	char poker[3];
	card_t hand[5], deck[5];

	while (getline(cin, s)) {
		istringstream iss(s);
		cout << "Hand: ";
		for (i = 0; i < 5; ++i) {
			iss >> poker;
			cout << poker << " ";
			hand[i] = card_t(poker);
		}
		cout << "Deck: ";
		for (i = 0; i < 5; ++i) {
			iss >> poker;
			cout << poker << " ";
			deck[i] = card_t(poker);
		}
		cout << "Best hand: " << level[solve(hand, deck)] << endl;
	}
	return 0;
}

