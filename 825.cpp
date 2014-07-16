#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <cstring>

using namespace std;

/*
 * G[i][j] = G[i - 1][j] + G[i][j - 1];
 * 代表当前(i, j)这个点可以由其左、右两点到达，故到达这点的路径数就为左、右两点路径数的和。
 */

string line;
int cases;
int n, m;
int G[201][201];
bool isblock[201][201];

int main() {
    cin >> cases;

    while (cases-- > 0) {
        cin >> n >> m;
        cin.ignore();
        memset(G, 0, sizeof(G));
        memset(isblock, 0, sizeof(isblock));

        for (int i = 0; i < n; ++i) {
            getline(cin, line);
            istringstream iss(line);
            int street, x;
            iss >> street;
            while (iss >> x)
                isblock[street][x] = true;
        }

        G[1][1] = 1;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                if (i == 1 && j == 1)
                    continue;
                int add1 = isblock[i - 1][j] ? 0 : G[i - 1][j];
                int add2 = isblock[i][j - 1] ? 0 : G[i][j - 1];
                G[i][j] = add1 + add2;
            }

        cout << G[n][m] << endl;
        if (cases)
            cout << endl;
    }
    return 0;
}
