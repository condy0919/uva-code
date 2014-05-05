#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdio>

/*
 * 1) a * Va + Vb  --> reduce (n+a)/2
 * 2) Vb + a * Va  --> reduce (n+2a)/2
 * so the No.2 is better, we take this category.
 */

using namespace std;

struct agency {
    string name;
    int cost;
    agency(const string& s = "", int _cost = 0):name(s), cost(_cost) {}
    bool operator<(const agency& rh) const {
        if (cost == rh.cost)
            return name < rh.name;
        return cost < rh.cost;
    }
};

char name[20];
int T, cases = 1;
int N, M, L;
int dolla, dollb;

int solve() {
    int n = N, m = M;
    int ret = 0;
    while (n > m) {
        if (n / 2 >= m) {
            if ((n - n / 2) * dolla < dollb)
                ret += (n - n / 2) * dolla;
            else
                ret += dollb;
            n /= 2;
        } else {
            ret += (n - m) * dolla;
            n = m;
        }
    }
    return ret;
}

int main() {
    cin >> T;
    while (cases <= T) {
        printf("Case %d\n", cases++);
        scanf("%d%d%d\n", &N, &M, &L);
        vector<agency> a;
        for (int i = 0; i < L; ++i) {
            scanf("%[^:]:%d,%d\n", name, &dolla, &dollb);
            a.push_back(agency(name, solve()));
        }
        sort(a.begin(), a.end());
        for (int i = 0; i < a.size(); ++i)
            cout << a[i].name << " " << a[i].cost << endl;
    }
    return 0;
}
