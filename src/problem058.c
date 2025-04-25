// Spiral Primes

// 37 36 35 34 33 32 31
// 38 17 16 15 14 13 30
// 39 18  5  4  3 12 29
// 40 19  6  1  2 11 28
// 41 20  7  8  9 10 27
// 42 21 22 23 24 25 26
// 43 44 45 46 47 48 49

// To upper right:  1, 3, 13, 31, ... -> 4n^2 - 10n + 7
// To upper left:   1, 5, 17, 37, ... -> 4n^2 -  8n + 5
// To bottom left:  1, 7, 21, 43, ... -> 4n^2 -  6n + 3
// To bottom right: 1, 9, 25, 49, ... -> 4n^2 -  4n + 1 = (2n - 1)^2

// Clearly the bottom right numbers are not prime

#include <stdio.h>

int is_prime(long long target)
{
    if (target < 2LL) {
        return 0;
    }

    if (target == 2LL) {
        return 1;
    }

    if (target % 2LL == 0LL) {
        return 0;
    }

    for (long long d = 3LL; d * d <= target; d += 2LL) {
        if (target % d == 0LL) {
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    long long n = 2;

    long long count = 0;
    long long num_of_diagonal_numbers = 5;

    while (1) {
        long long upper_right = 4 * n * n - 10 * n + 7;
        long long upper_left = 4 * n * n - 8 * n + 5;
        long long bottom_left = 4 * n * n - 6 * n + 3;

        if (is_prime(upper_right)) {
            count++;
        }

        if (is_prime(upper_left)) {
            count++;
        }

        if (is_prime(bottom_left)) {
            count++;
        }

        if (10 * count < num_of_diagonal_numbers) {
            break;
        }

        n++;
        num_of_diagonal_numbers += 4;
    }

    printf("%lld\n", 2 * n - 1);

    return 0;
}
