#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
#include <sstream>
#include <cstring>

/*
 * 错在下标啊。。不应该犯这种错啊。。
 */

using namespace std;

struct team_t {
	int team_id;
	bool problem_state[10];
	int solved;
	int submission_before_ac[10];
	int total_time[10];
	int time_used;

	bool operator<(const team_t& rh) const {
		if (solved != rh.solved)
			return solved > rh.solved;
		if (time_used != rh.time_used)
			return time_used < rh.time_used;
		return team_id < rh.team_id;
	}
};

team_t team[101];

int main()
{
	int total_test;
	int team_id, problem_id, time;
	char state;

	cin >> total_test;
	cin.ignore();
	cin.ignore();
	while (total_test-- > 0) {
		string str;
		bool vis[101] = {false};
		memset(team, 0, sizeof(team));

		while (getline(cin, str) && str.length() > 0) {
			istringstream iss(str);
			iss >> team_id >> problem_id >> time >> state;
			vis[team_id] = true;
			team[team_id].team_id = team_id;

			if (team[team_id].problem_state[problem_id])
				continue;

			if (state == 'C') {
				team[team_id].problem_state[problem_id] = true;
				++team[team_id].solved;
				team[team_id].total_time[problem_id] = team[team_id].submission_before_ac[problem_id] * 20 + time;
			} else if (state == 'I') {
				++team[team_id].submission_before_ac[problem_id];
			}
		}
		for (int i = 1; i <= 100; ++i)
			team[i].time_used = accumulate(team[i].total_time+1, team[i].total_time+10, 0);
		sort(team+1, team+101);
		//sort(team+1, team+100);
		for (int i = 1; i <= 100; ++i) {
			if (!vis[team[i].team_id])
				continue;
			cout << team[i].team_id << " " << team[i].solved << " " << team[i].time_used << endl;
		}
		if (total_test)
			cout << endl;
	}
	return 0;
}
