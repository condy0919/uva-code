#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>

using namespace std;

unsigned f[77] = {0, 1, 2, 2};

int main() {
    for (int i = 4; i < 77; ++i)
        f[i] = f[i - 2] + f[i - 3];
    
    int n;
    while (cin >> n)
        cout << f[n] << endl;

    return 0;
}

