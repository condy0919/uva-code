#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdio>

using namespace std;

struct  elem_t {
	int points;
	int wins;
	int ties;
	int loses;
	int scores, against;
	int game_cnt;
	string name;
};

bool cmp(const elem_t& a, const elem_t& b)
{
	if (a.points != b.points)
		return a.points > b.points;
	if (a.wins != b.wins)
		return a.wins > b.wins;
	if (a.scores-a.against != b.scores-b.against)
		return a.scores-a.against > b.scores-b.against;
	if (a.scores != b.scores)
		return a.scores > b.scores;
	if (a.game_cnt != b.game_cnt)
		return a.game_cnt < b.game_cnt;
	return strcasecmp(a.name.c_str(), b.name.c_str()) < 0;
}

int main()
{
	int N;
	vector<elem_t> vec;

	cin >> N;
	cin.ignore();
	while (N-- > 0) {
		string tournament;
		getline(cin, tournament);

		cout << tournament << endl;

		int T;
		cin >> T;
		cin.ignore();
		vec.resize(T);

		for (int i = 0; i < T; ++i) {
			string s;
			vec[i].points=vec[i].against=vec[i].scores=vec[i].loses=vec[i].ties=vec[i].wins=vec[i].game_cnt=0;
			getline(cin, s);
			vec[i].name = s;
		}

		int G;
		cin >> G;
		cin.ignore();
		string str;

		for (int i = 0; i < G; ++i) {
			getline(cin, str);
			int left = str.find('#'), right = str.rfind('#');

			string team1_name(str.substr(0, left));
			string team2_name(str.substr(right+1));

			++left;
			istringstream iss(str.substr(left));
			int team1_score, team2_score;

			iss >> team1_score;
			char __;
			iss >> __;
			iss >> team2_score;

			vector<elem_t>::iterator i1, i2;
			for (i1 = vec.begin(); i1 != vec.end(); ++i1)
				if (i1->name == team1_name)
					break;
			for (i2 = vec.begin(); i2 != vec.end(); ++i2)
				if (i2->name == team2_name)
					break;

			++i1->game_cnt;
			i1->against += team2_score;
			i1->scores += team1_score;
			++i2->game_cnt;
			i2->against += team1_score;
			i2->scores += team2_score;

			if (team1_score > team2_score) {
				i1->points += 3;
				i1->wins++;
				i2->loses++;
			} else if (team1_score == team2_score) {
				i1->points += 1;
				i2->points += 1;
				i1->ties += 1;
				i2->ties += 1;
			} else {
				i1->loses++;
				i2->points += 3;
				i2->wins++;
			}
		}

		sort(vec.begin(), vec.end(), cmp);
		for (int k = 0; k < vec.size(); ++k) {
			printf("%d) %s %dp, %dg (%d-%d-%d), %dgd (%d-%d)\n",
					k+1, vec[k].name.c_str(), vec[k].points,
					vec[k].game_cnt, vec[k].wins, vec[k].ties, vec[k].loses,
					vec[k].scores-vec[k].against,
					vec[k].scores, vec[k].against);
		}
		if (N != 0)
			putchar('\n');
	}
	return 0;
}

