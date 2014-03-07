#include <iostream>
#include <cstdio>
#include <map>
#include <string>
#include <cstring>

/*
 * 思路依旧混乱啊。
 */

using namespace std;

map<string, int> ref;
static int seq[34] = {1,2,3,4,5,6,7,8,9,11,12,13,14,15,16,17,18,19,21,22,23,24,25,26,27,28,29,31,32,33,34,35,36,37};
const char* mahjong_names[] = {
	"", "1T", "2T", "3T", "4T", "5T", "6T", "7T", "8T", "9T",// 1-9
	"", "1S", "2S", "3S", "4S", "5S", "6S", "7S", "8S", "9S",// 11-19
	"", "1W", "2W", "3W", "4W", "5W", "6W", "7W", "8W", "9W",// 21-29
	"", "DONG", "NAN", "XI", "BEI", "ZHONG", "FA", "BAI"// 31-37
};

int cnt[38];

void init()
{
	for (int i = 1; i <= 37; ++i) {
		if (mahjong_names[i][0] == '\0')
			continue;
		ref[mahjong_names[i]] = i;
	}
}

bool dfs(int pairs, int seq_idx)
{
	if (pairs == 4)
		return true;
	if (seq_idx == 34)
		return false;
	int mahjong_no = seq[seq_idx];
	if (!cnt[mahjong_no])
		return dfs(pairs, seq_idx + 1);


	// 3个相同的牌
	if (cnt[mahjong_no] >= 3) {
		cnt[mahjong_no] -= 3;
		if (dfs(pairs + 1, seq_idx)) {
			cnt[mahjong_no] += 3;
			return true;
		}
		cnt[mahjong_no] += 3;
	}
	// 3个连续的牌
	if (mahjong_no < 31 && cnt[mahjong_no] && cnt[mahjong_no + 1] && cnt[mahjong_no + 2]) {
		--cnt[mahjong_no], --cnt[mahjong_no + 1], --cnt[mahjong_no + 2];
		if (dfs(pairs + 1, seq_idx)) {
			++cnt[mahjong_no], ++cnt[mahjong_no + 1], ++cnt[mahjong_no + 2];
			return true;
		}
		++cnt[mahjong_no], ++cnt[mahjong_no + 1], ++cnt[mahjong_no + 2];
	}
	return false;
}

int main()
{
	int t = 0;
	string mahjong;

	init();
	while (cin >> mahjong, mahjong != "0") {
		memset(cnt, 0, sizeof(cnt));
		++cnt[ref[mahjong]];
		for (int i = 0; i < 12; ++i) {
			cin >> mahjong;
			++cnt[ref[mahjong]];
		}
		printf("Case %d:", ++t);
		bool flag = false;

		// 决定正在听哪张牌
		for (int i = 0; i < 34; ++i) {
			if (cnt[seq[i]] == 4)
				continue;
			++cnt[seq[i]];
			// 决定首个对子
			for (int j = 0; j < 34; ++j) {
				int no = seq[j];
				if (cnt[no] >= 2) {
					cnt[no] -= 2;
					if (dfs(0, 0)) {
						printf(" %s", mahjong_names[seq[i]]);
						flag = true;
						cnt[no] += 2;
						break;
					}
					cnt[no] += 2;
				}
			}
			--cnt[seq[i]];
		}
		puts(flag ? "" : " Not ready");
	}
	return 0;
}
