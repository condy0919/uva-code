#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int M;

struct segment {
    int l, r;
    segment(int _l = 0, int _r = 0):l(_l), r(_r) {}

    bool operator<(const segment& rh) const {
        return l < rh.l;
    }

    friend istream& operator>>(istream& in, segment& rh) {
        in >> rh.l >> rh.r;
        return in;
    }

    friend ostream& operator<<(ostream& out, segment& rh) {
        out << rh.l << " " << rh.r << endl;
        return out;
    }
};

void solve(vector<segment>& sv, int M, vector<segment>& ans)
{
    int left = 0;
    int i = 0;
    while (left < M) {
        int rightest = 0, k = -1;
        for (; i < sv.size() && sv[i].l <= left; ++i)
            if (sv[i].r > rightest) {
                rightest = sv[i].r;
                k = i;
            }
        if (k == -1) {
            ans.clear();
            return;
        }
        left = rightest;
        ans.push_back(sv[k]);
    }
}

int main()
{
    int T;
    int M;
    segment v;

    cin >> T;
    while (T-- > 0) {
        cin >> M;

        vector<segment> sv, ans;
        while (cin >> v, v.l || v.r)
            if (v.l < M && v.r > 0)
                sv.push_back(v);
        sort(sv.begin(), sv.end());
        solve(sv, M, ans);

        cout << ans.size() << endl;
        for (int i = 0; i < ans.size(); ++i)
            cout << ans[i];
        if (T)
            cout << endl;
    }
}
