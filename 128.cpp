#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <numeric>
#include <cstdint>

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    const uint32_t g = 34943;

    string line;
    while (getline(cin, line) && line[0] != '#') {
        uint32_t v = accumulate(line.begin(), line.end(), uint32_t(0),
                [&](uint32_t init, uint32_t val) {
                    return (256 * init + val) % g;
                });
        uint32_t r = (g - (v << 16) % g) % g; // add extra `%g` when line is empty
        cout << hex << uppercase << setfill('0')
            << setw(2) << (r >> 8) << " "
            << setw(2) << (r & 0xff) << endl;
    }

    return 0;
}
