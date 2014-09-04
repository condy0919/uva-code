#include <iostream>
#include <iomanip>
#include <bitset>

/*
 * 条件概率啊。所求即P(Ai|B) = P(Ai B) / P(B).
 */

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int T = 0;
    int N, r;
    double p[20];
    double total, individual[20];
    while (cin >> N >> r, N || r) {
        cout << "Case " << ++T << ":\n";
        for (int i = 0; i < N; ++i)
            cin >> p[i];

        total = 0.0;
        fill_n(individual, 20, 0.0);
        for (int i = 0; i < (1 << N); ++i) {
            if (bitset<32>(i).count() != r)
                continue;
            double prod = 1.0;
            for (int j = 0; j < N; ++j)
                prod *= (i & (1 << j)) ? p[j] : (1 - p[j]);
            total += prod;

            for (int j = 0; j < N; ++j)
                if (i & (1 << j))
                    individual[j] += prod;
        }
        for (int i = 0; i < N; ++i)
            cout << setiosflags(ios::fixed) << setprecision(6) << individual[i] / total << endl;
    }

    return 0;
}
