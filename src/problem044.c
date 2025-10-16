// Pentagon Numbers
// 5482660
// p_2167 = 7042750, p_1020 = 1560090
// p_2167 - p_1020 = 5482660 = p_1912, p_2167 + p_1020 = 8602840 = p_2395

#include <stdio.h>

#define LIMIT 3000

// Returns n * (3 * n - 1) / 2, the n-th pentagonal number
long long pentagonal_number(long long n)
{
    return n * (3 * n - 1) / 2;
}

int is_pentagonal(long long n)
{
    int l = 1;
    int r = 2;

    while (pentagonal_number(r - 1) < n) {
        r *= 2;
    }

    int m;
    long long p;

    do {
        m = (l + r) / 2;
        if (pentagonal_number(m) >= n) {
            r = m;
        } else {
            l = m + 1;
        }
    } while (l < r);

    return n == pentagonal_number(l);
}

int main(void)
{
    long long res = -1LL;

    for (int i = 2; i < LIMIT; i++) {
        long long p_i = pentagonal_number(i);
        for (int j = 1; j < i; j++) {
            long long p_j = pentagonal_number(j);
            if (is_pentagonal(p_i - p_j) && is_pentagonal(p_i + p_j)) {
                res = p_i - p_j;
                break;
            }
        }
        if (res > 0LL) {
            break;
        }
    }

    printf("%lld\n", res);

    return 0;
}
