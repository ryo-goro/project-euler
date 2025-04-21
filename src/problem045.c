// Triangular, Pentagonal, and Hexagonal

#include <stdio.h>

long long pentagon_number(int n)
{
    return (long long)n * (3 * n - 1) / 2;
}

long long hexagonal_number(int n)
{
    return (long long)n * (2 * n - 1);
}

int is_pentagonal(long long n)
{
    int l = 1;
    int r = 2;

    while (pentagon_number(r - 1) < n) {
        r *= 2;
    }

    int m;
    long long p;

    do {
        m = (l + r) / 2;
        if (pentagon_number(m) >= n) {
            r = m;
        } else {
            l = m + 1;
        }
    } while (l < r);

    return n == pentagon_number(l);
}

int main(void)
{
    // t(n) = n * (n + 1) / 2
    // p(n) = n * (3 * n - 1) / 2
    // h(n) = n * (2 * n - 1)

    // t(2 * n - 1) = (2 * n - 1) * (2 * n - 1 + 1) / 2 = n * (2 * n - 1) = h(n)
    // So all hexagonal numbers are triangle

    long long res;

    // t(285) = p(165) = h(143) = 40755
    // We need to find the next triangle number that is also pentagonal and hexagonal
    for (int n = 144; ; n++) {
        res = hexagonal_number(n);
        if (is_pentagonal(res)) {
            break;
        }
    }

    printf("%lld\n", res);

    return 0;
}
