// Truncatable Primes

#include <stdio.h>

#define LIMIT 11

int is_prime(long x)
{
    if (x < 2L) {
        return 0;
    }

    if (x == 2L) {
        return 1;
    }

    if (x % 2L == 0L) {
        return 0;
    }

    for (long d = 3L; d * d <= x; d += 2L) {
        if (x % d == 0L) {
            return 0;
        }
    }

    return 1;
}

int is_left_truncatable(long x)
{
    long power10 = 10L;

    while (power10 <= x) {
        power10 *= 10L;
    }

    while (x > 0L) {
        power10 /= 10L;
        if (!is_prime(x)) {
            return 0;
        }
        x %= power10;
    }
    
    return 1;
}

int is_right_truncatable(long x)
{
    while (x > 0L) {
        if (!is_prime(x)) {
            return 0;
        }
        x /= 10L;
    }

    return 1;
}

int is_truncatable(long x)
{
    if (!is_left_truncatable(x)) {
        return 0;
    }

    if (!is_right_truncatable(x / 10L)) {
        return 0;
    }

    return 1;
}

int main(void)
{
    long long res = 0LL;
    long target = 11L;

    for (int count = 0; count < LIMIT; target += 2L) {
        if (is_truncatable(target)) {
            res += target;
            count++;
        }
    }

    printf("%lld\n", res);

    return 0;
}
