#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>

/*
 * 起初，连测试数据都过不了啊。。。原来又是没有初始化啊。。。
 * 这题啊，逻辑性太强了。。。还好有很多测试数据。。
 * 比较奇怪的是，一直runtime error，把数组开大一点后就AC了。。。
 * 奇怪。
 */

using namespace std;

enum { DIVINE, HUMAN, EVIL, LYING };// description about type
enum { DAY, NIGHT };// about TIME
enum { PEOPLE, TIME };// about content type

struct chat_t {
	int speaker, object, object_type;// object_type: store people_type or time_type; object: used for specify people
	bool negative, content;

	chat_t() {
		negative = false;
		content = PEOPLE;
	}
};

int n;
bool vis[10], have_solution;
int day_or_night;
int type[10];// about people_type
int last[10];// last[5] for day_or_night
int cnt[10];// count for duction, cnt[5] for day_or_night
chat_t statements[55];

inline int c2i(char ch)
{
	return ch - 'A';
}

inline char i2c(int x)
{
	return x + 'A';
}

void read_info()
{
	string s;
	for (int i = 0; i < n; ++i) {
		cin >> s;
		statements[i].speaker = c2i(s[0]);
		vis[c2i(s[0])] = true;

		cin >> s;
		if (s == "It" )
			statements[i].content = TIME;
		else if (s == "I")
			statements[i].object = statements[i].speaker;
		else {
			statements[i].object = c2i(s[0]);
			vis[c2i(s[0])] = true;
		}

		cin >> s >> s;
		if (s == "not") {
			statements[i].negative = true;
			cin >> s;
		}
		if (statements[i].content == TIME) {// about time
			if (s == "day.")
				statements[i].object_type = DAY;
			else
				statements[i].object_type = NIGHT;
		} else {// about people
			if (s == "divine.")
				statements[i].object_type = DIVINE;
			else if (s == "human.")
				statements[i].object_type = HUMAN;
			else if (s == "evil.")
				statements[i].object_type = EVIL;
			else
				statements[i].object_type = LYING;
		}
	}
}

// check only for people_type
bool is_truth(const chat_t& statement)
{
	int speaker = statement.speaker, object = statement.object;
	int object_type = statement.object_type;
	int negative = statement.negative;

	// check himself
	if (speaker == object) {
		if (type[speaker] == DIVINE) {
			// divine say he is not divine
			if (negative == true && object_type == DIVINE)
				return false;
			// divine say he is (human, evil, lying)
			if (negative == false && (object_type == HUMAN || object_type == EVIL || object_type == LYING))
				return false;
		} else if (type[speaker] == HUMAN) {
			if (day_or_night == DAY) {
				// human say he is (evil, divine, lying)
				if (negative == false && (object_type == EVIL || object_type == DIVINE || object_type == LYING))
					return false;
				// human say he is not human
				if (negative == true && object_type == HUMAN)
					return false;
			} else {
				// human say he is (human, lying)
				if (negative == false && (object_type == HUMAN || object_type == LYING))
					return false;
				// human say he is not (human, lying)
				if (negative == true && (object_type == DIVINE || object_type == EVIL || object_type == LYING))
					return false;
			}
		} else if (type[speaker] == EVIL) {
			// evil say he is (evil, lying)
			if (negative == false && (object_type == EVIL || object_type == LYING))
				return false;
			// evil say he is not (divine, human)
			if (negative == true && (object_type == DIVINE || object_type == HUMAN))
				return false;
		}
	} else {
		if (type[speaker] == DIVINE) {
			// lying check
			if (object_type == LYING) {
				if (negative == false) {
					if (type[object] == DIVINE || (type[object] == HUMAN && day_or_night == DAY))
						return false;
				} else {
					if (type[object] == EVIL || (type[object] == HUMAN && day_or_night == NIGHT))
						return false;
				}
				return true;
			}
			// he say X is (...)
			if (negative == false && type[object] != object_type)
				return false;
			// he say X is not (...)
			if (negative == true && type[object] == object_type)
				return false;
		} else if (type[speaker] == HUMAN) {
			// lying check
			if (day_or_night == DAY) {
				if (object_type == LYING) {
					if (negative == false) {
						if (type[object] == DIVINE || (type[object] == HUMAN && day_or_night == DAY))
							return false;
					} else {
						if (type[object] == EVIL || (type[object] == HUMAN && day_or_night == NIGHT))
							return false;
					}
					return true;
				}
				// he say X is (...)
				if (negative == false && type[object] != object_type)
					return false;
				// he say X is not (...)
				if (negative == true && type[object] == object_type)
					return false;
			} else {
				// lying check
				if (object_type == LYING) {
					if (negative == false) {
						if ((type[object] == HUMAN && day_or_night == NIGHT) || type[object] == EVIL)
							return false;
					} else {
						if ((type[object] == HUMAN && day_or_night == DAY) || type[object] == DIVINE)
							return false;
					}
					return true;
				}
				// he say X is (...)
				if (negative == false && type[object] == object_type)
					return false;
				// he say X is not (...)
				if (negative == true && type[object] != object_type)
					return false;
			}
		} else if (type[speaker] == EVIL) {
			// lying check
			if (object_type == LYING) {
				if (negative == false) {
					if ((type[object] == HUMAN && day_or_night == NIGHT) || type[object] == EVIL)
						return false;
				} else {
					if ((type[object] == HUMAN && day_or_night == DAY) || type[object] == DIVINE)
						return false;
				}
				return true;
			}
			// evil say X is (...)
			if (negative == false && type[object] == object_type)
				return false;
			// evil say X is not (...)
			if (negative == true && type[object] != object_type)
				return false;
		}
	}
	return true;
}

bool check()
{
	int i;
	int speaker;

	for (i = 0; i < n; ++i) {
		if (statements[i].content == TIME) {
			speaker = statements[i].speaker;
			if (type[speaker] == DIVINE || (type[speaker] == HUMAN && day_or_night == DAY)) {
				if (statements[i].negative == false && statements[i].object_type != day_or_night)
					return false;
				if (statements[i].negative == true && statements[i].object_type == day_or_night)
					return false;
			} else {
				if (statements[i].negative == false && statements[i].object_type == day_or_night)
					return false;
				if (statements[i].negative == true && statements[i].object_type != day_or_night)
					return false;
			}
		} else if (!is_truth(statements[i]))
			return false;
	}
	return true;
}

void dfs(int pos)
{
	if (pos == 5) {
		if (check()) {
			have_solution = true;

			// store count info
			for (int i = 0; i < 5; ++i)
				if (vis[i] && last[i] != type[i])
					++cnt[i];
			vis[5] = true;
			if (last[5] != day_or_night)
				++cnt[5];
			// store assumpation
			for (int i = 0; i < 5; ++i)
				if (vis[i])
					last[i] = type[i];
			last[5] = day_or_night;
		}
		return;
	}
	// the person not exist
	if (!vis[pos]) {
		dfs(pos + 1);
		return;
	}

	// enumerate the person's type
	for (type[pos] = DIVINE; type[pos] <= EVIL; ++type[pos])
		dfs(pos + 1);
}

int main()
{
	int round = 0;
	bool flag;

	while (cin >> n, n) {
		have_solution = false;
		memset(cnt, 0, sizeof(cnt));
		memset(vis, 0, sizeof(vis));
		memset(last, -1, sizeof(last));
		memset(type, 0, sizeof(type));
		memset(statements, 0, sizeof(statements));
		flag = false;
		read_info();

		for (day_or_night = DAY; day_or_night <= NIGHT; ++day_or_night)
			dfs(0);

		printf("Conversation #%d\n", ++round);
		if (!have_solution) {
			puts("This is impossible.");
			putchar('\n');
			continue;
		}
		for (int i = 0; i < 6; ++i) {
			if (!vis[i] || cnt[i] != 1)
				continue;
			flag = true;
			// output time info
			if (i == 5) {
				printf("It is %s.\n", last[5] == DAY ? "day" : "night");
				continue;
			}
			printf("%c is ", i2c(i));
			if (last[i] == DIVINE)
				puts("divine.");
			else if (last[i] == HUMAN)
				puts("human.");
			else if (last[i] == EVIL)
				puts("evil.");
		}
		if (!flag)
			puts("No facts are deducible.");
		putchar('\n');
	}
	return 0;
}
