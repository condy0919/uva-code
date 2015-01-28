#include <cstdio>
#include <limits>

using namespace std;

int main() {
    int Sp, Sq, N;
    while (scanf("%d%d%d", &N, &Sp, &Sq) == 3) {
        int a, b;
        long long k = numeric_limits<long long>::max();
        for (int i = 0; i < 32; ++i) {
            for (int j = 0; j < 32; ++j) {
                long long pn = (N - 1) * Sp;
                long long _k = ((pn + (pn << i)) >> j) + Sq;
                if (_k < N * Sq)
                    break;
                if (_k < k) {
                    k = _k;
                    a = i;
                    b = j;
                }
            }
        }
        printf("%lld %d %d\n", k, a, b);
    }
    return 0;
}
