#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

/*
 * O = A
 * O = OAB
 * O = BOA
 * O结构必定为奇数个，则若O的长度为偶数，则肯定是不符合的情况。
 */

int parse(const string& s) {
    if (s.length() == 1 && s[0] == 'A')
        return 0;
    int n = s.length();
    if (n % 2 == 0)
        return 3;
    if (s[n - 1] == 'B' && s[n - 2] == 'A')
        return 1;
    if (s[0] == 'B' && s[n - 1] == 'A')
        return 2;
    return 3;
}

int main() {
    int tests;
    string s;

    const char* ref[4] = {
        "SIMPLE", "FULLY-GROWN", "MUTAGENIC", "MUTANT"
    };

    cin >> tests;
    while (tests-- > 0) {
        cin >> s;
        cout << ref[parse(s)] << endl;
    }
    return 0;
}
