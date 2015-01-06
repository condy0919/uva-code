#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

/*
 * 样例的Output有问题。
 */

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    vector<vector<string>> svvec;
    string line, s;
    while (getline(cin, line)) {
        istringstream iss(line);
        vector<string> svec;
        while (iss >> s)
            svec.push_back(s);
        svvec.push_back(svec);
    }
    int longest =
        max_element(svvec.begin(), svvec.end(),
                    [](const vector<string> &lhs, const vector<string> &rhs) {
                        return lhs.size() < rhs.size();
                    })->size();
    vector<int> lim(longest);
    for (int i = 0; i < svvec.size(); ++i)
        for (int j = 0; j < svvec[i].size(); ++j)
            lim[j] = max(lim[j], static_cast<int>(svvec[i][j].length()));

    for (int i = 0; i < svvec.size(); ++i) {
        for (int j = 0; j < svvec[i].size() - 1; ++j)
            cout << left << setw(lim[j] + 1) << svvec[i][j];
        cout << svvec[i].back() << '\n';
    }

    return 0;
}
