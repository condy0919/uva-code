#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <algorithm>

using namespace std;

pair<string, string> parse_address(const string& s) {
    int k = s.find('@');
    return {s.substr(0, k), s.substr(k + 1)};
}

int main() {
    int k;
    string s, t, user1, user2, mta1, mta2;
    set<string> addr;

    while (cin >> s && s != "*") {
        cin >> s >> k;
        while (k-- > 0) {
            cin >> t;
            addr.insert(t + "@" + s);
        }
    }

    while (cin >> s && s != "*") {
        pair<string, string> pr = parse_address(s);
        string &user1 = pr.first, &mta1 = pr.second;

        vector<string> mta;
        map<string, vector<string>> dest;
        set<string> vis;
        while (cin >> t && t != "*") {
            pair<string, string> pr = parse_address(t);
            string &user2 = pr.first, &mta2 = pr.second;

            if (vis.count(t))
                continue;
            vis.insert(t);
            if (!dest.count(mta2)) {
                mta.push_back(mta2);
                dest[mta2] = vector<string>();
            }
            dest[mta2].push_back(t);
        }
        getline(cin, t);

        string data;
        while (getline(cin, t) && t[0] != '*')
            data += "     " + t + "\n";

        for (const auto& user : mta) {
            const vector<string>& users = dest[user];
            cout << "Connection between " << mta1 << " and " << user << "\n";
            cout << "     HELO " << mta1 << "\n";
            cout << "     250\n";
            cout << "     MAIL FROM:<" << s << ">\n";
            cout << "     250\n";
            bool ok = false;
            for (const auto& to : users) {
                cout << "     RCPT TO:<" << to << ">\n";
                if (addr.count(to)) {
                    ok = true;
                    cout << "     250\n";
                } else {
                    cout << "     550\n";
                }
            }
            if (ok) {
                cout << "     DATA\n";
                cout << "     354\n";
                cout << data << "     .\n";
                cout << "     250\n";
            }
            cout << "     QUIT\n";
            cout << "     221\n";
        }
    }
    return 0;
}
