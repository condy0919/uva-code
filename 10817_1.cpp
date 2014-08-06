#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <cstring>

#define rep(i, s, e) for (int i = s; i <= e; ++i)
#define pre(i, s, e) for (int i = s; i >= e; --i)

using namespace std;

int S, M, N, P;
int v;
int f[101][6562]; // 3^8
int w[101];
int applicant[101][10];

string line;
int c, sub;

int main() {
    ios::sync_with_stdio(false);

    while (cin >> S >> M >> N, S) {
        cin.ignore();
        int need[8] = { 2, 2, 2, 2, 2, 2, 2, 2 };
        v = 0;
        for (int i = 0; i < M; ++i) {
            getline(cin, line);
            istringstream iss(line);
            iss >> c;
            v += c;
            while (iss >> sub)
                if (need[sub - 1])
                    --need[sub - 1];
        }
        memset(applicant, 0, sizeof(applicant));
        for (int i = 1; i <= N; ++i) {
            getline(cin, line);
            istringstream iss(line);
            iss >> w[i];
            while (iss >> sub)
                applicant[i][sub - 1] = 1;
        }
        memset(f, 0x3f, sizeof(f));
        P = 0;
        for (int i = 0; i < S; ++i)
            P = 3 * P + 2;
        for (int i = 0; i <= P; ++i) {
            int t = i, p[9] = {0};
            for (int j = 0; j < S; ++j) {
                p[j] = t % 3;
                t /= 3;
            }
            int j = 0;
            for (j = 0; j < S && p[j] >= need[j]; ++j)
                ;
            if (j == S)
                f[0][i] = v;
        }

        rep(i, 1, N) {
            rep(j, 0, P) {
                f[i][j] = f[i - 1][j];
                int t = j, p[9] = {0};
                for (int k = 0; k < S; ++k) {
                    p[k] = t % 3;
                    t /= 3;
                }
                for (int k = 0; k < S; ++k)
                    if (applicant[i][k] && p[k] < 2)
                        ++p[k];
                t = 0;
                for (int k = S - 1; k >= 0; --k)
                    t = 3 * t + p[k];
                f[i][j] = min(f[i][j], f[i - 1][t] + w[i]);
            }
        }
        cout << f[N][0] << endl;
    }

    return 0;
}
