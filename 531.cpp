#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>

using namespace std;

/*
 * 经典的lcs，要输出lcs内容。
 */

enum { UP = 1, LEFT, LEFTUP };

string s, word;
int f[101][101];
int dir[101][101];
bool first;
vector<string> a, b;

void print_ans(int x, int y) {
    if (x == 0 || y == 0)
        return;

    if (dir[x][y] == LEFTUP) {
        print_ans(x - 1, y - 1);
        if (first) {
            first = false;
            cout << a[x - 1];
        } else {
            cout << " " << a[x - 1];
        }
    } else if (dir[x][y] == LEFT) {
        print_ans(x, y - 1);
    } else if (dir[x][y] == UP) {
        print_ans(x - 1, y);
    }
}


int main() {
    while (getline(cin, s)) {
        a.clear();
        b.clear();
        first = true;
        while (s != "#") {
            istringstream iss(s);
            while (iss >> word)
                a.push_back(word);
            getline(cin, s);
        }
        while (getline(cin, s), s != "#") {
            istringstream iss(s);
            while (iss >> word)
                b.push_back(word);
        }
        memset(f, 0, sizeof(f));

        for (int i = 0; i < a.size(); ++i) {
            for (int j = 0; j < b.size(); ++j) {
                if (a[i] == b[j]) {
                    f[i + 1][j + 1] = 1 + f[i][j];
                    dir[i + 1][j + 1] = LEFTUP;
                } else if (f[i + 1][j] < f[i][j + 1]) {
                    f[i + 1][j + 1] = f[i][j + 1];
                    dir[i + 1][j + 1] = UP;
                } else {
                    f[i + 1][j + 1] = f[i + 1][j];
                    dir[i + 1][j + 1] = LEFT;
                }
            }
        }

        print_ans(a.size(), b.size());
        cout << endl;
    }
    return 0;
}
