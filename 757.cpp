#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

struct lake {
    int id;
    int exp_fish, dec_fish;

    lake(int _ex = 0, int _dec = 0, int _id = 0):
        exp_fish(_ex), dec_fish(_dec), id(_id) {}

    bool operator<(const lake& rh) const {
        if (exp_fish == rh.exp_fish)
            return id > rh.id;
        return exp_fish < rh.exp_fish;
    }
};

int main()
{
    int h, n;
    bool first = false;
    while (cin >> n, n && cin >> h) {
        if (first)
            cout << endl;
        else
            first = true;

        vector<lake> lakes(n);
        for (int i = 0; i < n; ++i) {
            cin >> lakes[i].exp_fish;
            lakes[i].id = i;
        }
        for (int i = 0; i < n; ++i)
            cin >> lakes[i].dec_fish;

        int t[30] = {0}, v;
        for (int i = 1; i < n; ++i) {
            cin >> v;
            t[i] = t[i - 1] + v;
        }
        
        int max_fish = -1;
        vector<int> spend_time(n);
        for (int i = 0; i < n; ++i) {
            int left_time = h * 12 - t[i];
            vector<int> cur_time(n);

            if (left_time <= 0)
                break;

            priority_queue<lake> Q;
            int cur_fish = 0;
            for (int j = 0; j <= i; ++j)
                Q.push(lakes[j]);
            while (!Q.empty() && Q.top().exp_fish > 0 && left_time > 0) { 
                /*
                 * 看了许久，原来是这里错了。例如3个湖泊的情况，中间的初始鱼数为0,而2边的都不为0.
                 * 很明显可以看出来，中间的湖泊必定要跳过（要将尽可能多的时间放在第1个湖泊上）.
                 */
                lake e = Q.top(); Q.pop();
                cur_fish += e.exp_fish;

                --left_time;
                ++cur_time[e.id];

                e.exp_fish -= e.dec_fish;
                if (e.exp_fish > 0)
                    Q.push(e);
            }
            if (left_time > 0)
                cur_time[0] += left_time;
            if (cur_fish > max_fish) {
                max_fish = cur_fish;
                spend_time = cur_time;
            }
        }
        cout << spend_time[0] * 5;
        for (int i = 1; i < n; ++i)
            cout << ", " << spend_time[i] * 5;
        cout << endl << "Number of fish expected: " << max_fish << endl;
    }
    return 0;
}
