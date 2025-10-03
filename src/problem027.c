// Quadratic Primes
// -59231
// a = -61, b = 971

#include <stdio.h>

#define LIMIT 1000

long absolute(long x)
{
    return x < 0 ? -x : x;
}

long monic_quadratic(long a, long b, long n)
{
    return n * n + a * n + b;
}

int is_prime(long target)
{
    if (target < 2L) {
        return 0;
    }

    if (target == 2L) {
        return 1;
    }

    if (target % 2 == 0L) {
        return 0;
    }

    for (long d = 3; d * d <= target; d += 2) {
        if (target % d == 0L) {
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    long res_a, res_b;
    long max_len = 0;

    for (long b = -LIMIT; b <= LIMIT; b++) {
        long abs_b = absolute(b);

        if (!is_prime(abs_b)) {
            continue;
        }

        for (long a = -LIMIT + 1; a < LIMIT; a++) {
            long n = 1;

            for (; n <= abs_b; n++) {
                if (!is_prime(absolute(monic_quadratic(a, b, n)))) {
                    break;
                }
            }

            if (n > max_len) {
                res_a = a;
                res_b = b;
                max_len = n;
            }
        }
    }

    printf("%ld\n", res_a * res_b);

    return 0;
}
