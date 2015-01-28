#include <cstdio>
#include <cstring>

using namespace std;

int main() {
    int cases = 0;
    int n;
    int a[10], b[10], c[10];
    int state[10];

    while (scanf("%d", &n), n) {
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        memset(c, 0, sizeof(c));

        printf("Case %d: ", ++cases);
        for (int i = 0; i < n; ++i) {
            scanf("%d%d%d", &a[i], &b[i], &c[i]);
            state[i] = c[i];
        }

        int awake = 0, sleepy = 0;
        for (int i = 0; i < n; ++i) {
            if (c[i] <= a[i])
                ++awake;
            else
                ++sleepy;
        }

        if (!sleepy) {
            puts("1");
            continue;
        }

        for (int t = 2; ; ++t) {
            int loopedin = 0, fallin = 0, wake = 0;
            for (int i = 0; i < n; ++i) {
                ++c[i];
                if (c[i] == a[i] + 1) {
                    if (sleepy > awake) {
                        ++fallin;
                    } else {
                        c[i] = 1;
                    }
                } else if (c[i] > a[i] + b[i]) {
                    ++wake;
                    c[i] = 1;
                }
                if (c[i] == state[i])
                    ++loopedin;
            }
            sleepy += fallin - wake;
            awake = n - sleepy;
            if (!sleepy) {
                printf("%d\n", t);
                break;
            } else if (loopedin == n) {
                puts("-1");
                break;
            }
        }
    }
    return 0;
}
