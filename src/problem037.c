// Truncatable Primes
// 748317

#include <stdio.h>

#define LIMIT 11

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

int is_left_truncatable(long x)
{
    long power10 = 10;

    while (power10 <= x) {
        power10 *= 10;
    }

    while (x > 0L) {
        power10 /= 10;
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
        x /= 10;
    }

    return 1;
}

int is_truncatable(long x)
{
    if (!is_left_truncatable(x)) {
        return 0;
    }

    // Whether x is prime or not has already been checked by is_left_truncatable()
    // So we only need to check if x/10 (obtained by truncating x to 1 digit) is right-truncatable
    if (!is_right_truncatable(x / 10)) {
        return 0;
    }

    return 1;
}

int main(void)
{
    long long res = 0;
    long target = 11;   // Begin with the smallest 2-digit prime number

    // Truncatable numbers are 2-digit and prime
    // So at least they are all odd
    for (int count = 0; count < LIMIT; target += 2) {
        if (is_truncatable(target)) {
            res += target;
            count++;
        }
    }

    printf("%lld\n", res);

    return 0;
}
