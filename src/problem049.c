// Prime Permutations

#include <stdio.h>

#define LIMIT 10000
#define NUM_OF_DIGITS 4
#define BUF_LEN 32

#define swap(type, x, y)    do { type t = x; x = y; y = t; } while (0)

void reverse(int *a, int l, int r)
{
    for (int i = 0, h = (r - l) / 2; i < h; i++) {
        swap(int, a[l + i], a[r - 1 - i]);
    }
}

int next_permutation(int *a, int n)
{
    int i = n - 2;
    for (; i >= 0; i--) {
        if (a[i] < a[i + 1]) {
            break;
        }
    }

    if (i < 0) {
        reverse(a, 0, n);
        return 0;
    }

    int tmp = a[i];
    int j = n - 1;
    for (; j > i; j--) {
        if (a[j] > tmp) {
            break;
        }
    }

    swap(int, a[i], a[j]);
    reverse(a, i + 1, n);

    return 1;
}

void to_array(int *digits, int num_of_digits, int target)
{
    for (int i = num_of_digits - 1; i >= 0; i--) {
        digits[i] = target % 10;
        target /= 10;
    }
}

int to_int(const int *digits, int num_of_digits)
{
    int res = 0;
    for (int i = 0; i < num_of_digits; i++) {
        res = res * 10 + digits[i];
    }

    return res;
}

void make_sieve(int *sieve, int n)
{
    for (int i = 0; i < n; i++) {
        sieve[i] = 1;
    }

    sieve[0] = sieve[1] = 0;

    for (int i = 4; i < n; i += 2) {
        sieve[i] = 0;
    }

    for (int i = 3; i * i < n; i += 2) {
        if (sieve[i]) {
            for (int j = i * i; j < n; j += i) {
                sieve[j] = 0;
            }
        }
    }
}

int main(void)
{
    int prime[LIMIT];
    make_sieve(prime, LIMIT);

    int checked[LIMIT] = {0};
    checked[1487] = 1;

    int digits[NUM_OF_DIGITS];
    int buf[BUF_LEN];
    int buf_size;

    for (int target = LIMIT / 10; target < LIMIT; target++) {
        if (checked[target]) {
            continue;
        }

        if (!prime[target]) {
            continue;
        }

        buf[0] = target;
        buf_size = 1;

        to_array(digits, NUM_OF_DIGITS, target);

        while (next_permutation(digits, NUM_OF_DIGITS)) {
            int perm = to_int(digits, NUM_OF_DIGITS);
            checked[perm] = 1;

            if (prime[perm]) {
                buf[buf_size++] = perm;
            }
        }

        if (buf_size < 3) {
            continue;
        }

        int first, second, third, diff;

        for (int i = 0; i < buf_size - 2; i++) {
            first = buf[i];

            for (int j = i + 1; j < buf_size - 1; j++) {
                second = buf[j];
                diff = second - first;

                for (int k = j + 1; k < buf_size; k++) {
                    third = buf[k];
                    if (third - second == diff) {
                        printf("%d%d%d\n", first, second, third);
                        return 0;
                    }
                }
            }
        }
    }

    return 1;
}
