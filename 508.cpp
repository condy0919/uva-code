#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <sstream>

#define inf 0x7f7f7f7f

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    string morse[256];
    string line;
    string s;
    char ch;
    while (getline(cin, line), line != "*") {
        if (line.empty())
            continue;
        istringstream iss(line);
        iss >> ch >> s;
        morse[ch] = s;
    }
    map<string, vector<string>> morse_map;
    while (getline(cin, line), line != "*") {
        if (line.empty())
            continue;
        string m =
            accumulate(line.begin(), line.end(), string(""),
                       [&](string init, char ch) { return init + morse[ch]; });
        morse_map[m].push_back(std::move(line));
    }
    while (cin >> line, line != "*") {
        auto iter = morse_map.find(line);
        if (iter == morse_map.end()) {
            vector<string> ans;
            int len = inf;
            for (const auto& i : morse_map) {
                const auto &ref_longer = line.length() > i.first.length() ? line : i.first;
                const auto &ref_shorter = line.length() > i.first.length() ? i.first : line;
                int len_longer = ref_longer.length(),
                    len_shorter = ref_shorter.length();

                if (len_longer == len_shorter)
                    continue;
                if (!ref_longer.compare(0, len_shorter, ref_shorter)) {
                    if (len == len_longer - len_shorter) {
                        copy(i.second.begin(), i.second.end(), back_inserter(ans));
                    } else if (len > len_longer - len_shorter) {
                        len = len_longer - len_shorter;
                        ans.clear();
                        copy(i.second.begin(), i.second.end(), back_inserter(ans));
                    }
                }
            }
            cout << ans[0] << '?';
        } else {
            cout << iter->second[0];
            if (iter->second.size() > 1)
                cout << '!';
        }
        cout << '\n';
    }

    return 0;
}
