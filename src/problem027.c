// Quadratic Primes

#include <stdio.h>

#define PRIMES_NUM 10000
#define LIMIT 1000

int composite[PRIMES_NUM];
int primes[PRIMES_NUM];
int primes_len;

void init_globals(void)
{
    composite[0] = composite[1] = 1;

    for (int i = 4; i < PRIMES_NUM; i += 2) {
        composite[i] = 1;
    }

    for (int i = 3; i * i < PRIMES_NUM; i += 2) {
        if (!composite[i]) {
            for (int j = i * i; j < PRIMES_NUM; j += i) {
                composite[j] = 1;
            }
        }
    }

    for (int i = 0; i < PRIMES_NUM; i++) {
        if (!composite[i]) {
            primes[primes_len++] = i;
        }
    }
}

long absolute(long x)
{
    return x < 0 ? -x : x;
}

int is_prime(long x)
{
    x = absolute(x);

    if (x < PRIMES_NUM) {
        return !composite[x];
    }

    for (int i = 0; i < primes_len; i++) {
        long p = primes[i];
        if (x < p * p) {
            return 1;
        }
        if (x % p == 0) {
            return 0;
        }
    }

    return 1;
}

long f(long a, long b, long n)
{
    return n * n + a * n + b;
}

int main(void)
{
    init_globals();

    long a, b;
    long max_len = 0L;

    for (long bb = -LIMIT; bb <= LIMIT; bb++) {
        if (!is_prime(bb)) {
            continue;
        }

        long bb_abs = absolute(bb);

        for (long aa = -LIMIT + 1; aa < LIMIT; aa++) {
            long n = 1L;
            for (; n <= bb_abs; n++) {
                if (!is_prime(f(aa, bb, n))) {
                    break;
                }
            }

            if (n > max_len) {
                a = aa;
                b = bb;
                max_len = n;
            }
        }
    }

    printf("%ld\n", a * b);

    return 0;
}
