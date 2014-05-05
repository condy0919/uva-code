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

void remove(int start, int l, int r, vector<segment>& sv)
{
    while (start < sv.size() && sv[start].r <= l)
        sv.erase(sv.begin() + start);
}

vector<segment> solve(vector<segment>& sv)
{
    int left = 0, right = M;

    int head = 0, tail = 0;
    vector<segment> ret;
    while (head < sv.size()) {
        if (sv[head].l > left) // cannot cover
            return vector<segment>();

        int rightest = sv[head].r, k = head;
        for (tail = head + 1; tail < sv.size() && sv[tail].l <= left; ++tail)
            if (sv[tail].r > rightest) {
                rightest = sv[tail].r;
                k = tail;
            }
        left = rightest;
        remove(tail, left, M, sv);
        head = tail;
        ret.push_back(sv[k]);
        if (rightest >= M)
            return ret;
    }
    return vector<segment>();
}

int main()
{
    int T;
    segment v;

    cin >> T;
    while (T-- > 0) {
        cin >> M;

        vector<segment> sv;
        while (cin >> v, v.l || v.r)
            if (v.l < M)
                sv.push_back(v);

        sort(sv.begin(), sv.end());
        remove(0, 0, M, sv);
        vector<segment> ans = solve(sv);

        cout << ans.size() << endl;
        for (int i = 0; i < ans.size(); ++i)
            cout << ans[i];
        if (T)
            cout << endl;
    }
    return 0;
}
