#include <cstdio>

using namespace std;

inline unsigned low_bit(unsigned x) { return x & -x; }

unsigned high_bit(unsigned x) {
    while (x - low_bit(x) != 0)
        x -= low_bit(x);
    return x;
}

int main() {
    int n;
    auto show_bits = [](unsigned x) {
        unsigned f0 = x & 0xff, f1 = (x & 0xff00) >> 8,
                 f2 = (x & 0xff0000) >> 16, f3 = (x & 0xff000000) >> 24;
        printf("%u.%u.%u.%u\n", f3, f2, f1, f0);
    };
    while (scanf("%d", &n) == 1) {
        unsigned _add = -1, _or = 0;
        unsigned f0, f1, f2, f3, t;
        while (n-- > 0) {
            scanf("%u.%u.%u.%u", &f3, &f2, &f1, &f0);
            t = ((f3 * 256 + f2) * 256 + f1) * 256 + f0;
            _add &= t;
            _or |= t;
        }

        unsigned netmask;
        if (high_bit(_add ^ _or) == 0) {
            netmask = -1;
        } else {
            netmask = ~((high_bit(_add ^ _or) << 1) - 1);
        }
        show_bits(netmask & t);
        show_bits(netmask);
    }
    return 0;
}
