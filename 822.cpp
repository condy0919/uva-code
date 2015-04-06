// Copy from http://webcache.googleusercontent.com/search?q=cache:yB0NKfJp6r8J:https://github.com/morris821028/UVa/blob/master/temp/822%2520-%2520Queue%2520and%2520A.cpp+&cd=5&hl=en&ct=clnk

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <bitset>
#include <utility>
#include <functional>
#include <numeric>
#include <limits>
#include <cmath>
#include <cctype>
#include <cstring>

#define rep(i, s, e) for (int i = s; i <= e; ++i)
#define pre(i, s, e) for (int i = s; i >= e; --i)

#define pi (acos(-1.0))
#define eps (1e-9)
#define inf 0x7f7f7f7f

using namespace std;

struct Staff {
    int pid;
    vector<int> proc_list;
    bool operator<(const Staff& rhs) const {
        return pid < rhs.pid;
    }
};

struct Job {
	int tid, st, proc;
	Job(int t = 0, int s = 0, int e = 0) : tid(t), st(s), proc(e) {}
};

struct cmpJob {
	bool operator()(const Job& a, const Job& b) const {
		return a.st > b.st;
	}
};

bool cmp(pair<int, int> a, pair<int, int> b) {
	if (a.first != b.first)
		return a.first < b.first;
	return a.second < b.second;
}

int main() {
    ios::sync_with_stdio(false);

	int N, M, cases = 0;
	while (cin >> N, N) {
		map<int, priority_queue<Job, vector<Job>, cmpJob>> scheduler;
		priority_queue<int, vector<int>, greater<int>> timeline;
		for (int i = 0; i < N; ++i) {
			int tid, num, t0, t, dt;
			cin >> tid >> num >> t0 >> t >> dt;
			for (int j = 0; j < num; ++j) {
				scheduler[tid].push(Job(tid, t0, t));
				timeline.push(t0);
				t0 += dt;
			}
		}
		cin >> M;
		Staff staffs[10];
		for (int i = 0; i < M; ++i) {
			int pid, num, tid;
			cin >> pid >> num;
			staffs[i].pid = pid;
			for (int j = 0; j < num; ++j) {
				cin >> tid;
				staffs[i].proc_list.push_back(tid);
			}
		}
		sort(staffs, staffs + M); // sort by pid
		int working[10] = {}, preReq[10] = {}, finReq[10] = {};
		int tot = -2, now;
		timeline.push(-1);
		while (!timeline.empty()) {
			now = timeline.top();
			timeline.pop();
			if (now == tot)
				continue;
			tot = now;
			for (int i = 0; i < M; ++i)
				if (working[i] && finReq[i] <= now)
					working[i] = 0;
			vector<pair<int, int>> D;
			for (int i = 0; i < M; ++i)
				if (working[i] == 0)
					D.emplace_back(preReq[i], i);
			sort(D.begin(), D.end(), cmp);
			for (int i = 0; i < D.size(); ++i) {
				Staff& u = staffs[D[i].second];
				for (int j = 0; j < u.proc_list.size(); ++j) {
					int tid = u.proc_list[j];
					if (!scheduler[tid].empty()) {
						Job tmp = scheduler[tid].top();
						if (tmp.st <= now) {
							scheduler[tid].pop();
							preReq[D[i].second] = now;
							finReq[D[i].second] = now + tmp.proc;
							working[D[i].second] = 1;
							timeline.push(finReq[D[i].second]);
							break;
						}
					}
				}
			}
		}
        cout << "Scenario " << ++cases << ": All requests are serviced within " << tot << " minutes.\n";
	}

    return 0;
}
