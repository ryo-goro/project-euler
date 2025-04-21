// Goldbach's Other Conjecture

#include <stdio.h>

int is_prime(long n)
{
    if (n < 2L) {
        return 0;
    }

    if (n == 2L) {
        return 1;
    }

    if (n % 2L == 0L) {
        return 0;
    }

    for (long d = 3L; d * d <= n; d += 2L) {
        if (n % d == 0L) {
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    long n;

    for (n = 9L; ; n += 2L) {
        if (is_prime(n)) {
            continue;
        }

        int found = 1;

        for (long i = 1L, square_2; ; i++) {
            square_2 = 2L * i * i;
            if (square_2 >= n) {
                break;
            }
            if (is_prime(n - square_2)) {
                found = 0;
                break;
            }
        }

        if (found) {
            break;
        }
    }

    printf("%ld\n", n);

    return 0;
}
