#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <sstream>
#include <functional>

using namespace std;

map<string, string> read_map() {
    map<string, string> ret;
    string line, subline;
    getline(cin, line);
    istringstream iss(line.substr(1, line.length() - 2));
    while (getline(iss, subline, ',')) {
        int pos = subline.find_first_of(':');
        string key = subline.substr(0, pos), val = subline.substr(pos + 1);
        ret[key] = val;
    }
    return ret;
}

void output(const vector<string>& vec) {
    bool first = true;
    for (const auto& i : vec) {
        if (first)
            first = false;
        else
            cout << ',';
        cout << i;
    }
}

void diff(map<string, string>& a, map<string, string>& b) {
    vector<string> v[3];
    vector<string> &adds = v[0], &rms = v[1], &chs = v[2];
    for (const auto& i : b) {
        if (a.find(i.first) == a.end()) {
            adds.push_back(i.first);
        } else {
            if (a[i.first] != i.second)
                chs.push_back(i.first);
            a.erase(i.first);
        }
    }
    for (const auto& i : a)
        rms.push_back(i.first);

    static char prefix[3] = {'+', '-', '*'};
    for (int i = 0; i < 3; ++i) {
        if (v[i].size() > 0) {
            cout << prefix[i];
            output(v[i]);
            cout << '\n';
        }
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    int T;
    (cin >> T).ignore();
    while (T-- > 0) {
        map<string, string> a = read_map();
        map<string, string> b = read_map();

        if (a == b)
            cout << "No changes\n\n";
        else
            diff(a, b);
    }
    return 0;
}
