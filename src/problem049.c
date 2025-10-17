// Prime Permutations
// 296962999629

#include <stdio.h>

#define LIMIT 10000
#define NUM_OF_DIGITS 4
#define BUF_LEN 32  // Good enough as long as it's >= NUM_OF_DIGITS! = 4! = 24

#define swap(type, x, y)    do { type t = x; x = y; y = t; } while (0)

void reverse_arr(int *arr, int begin, int end)
{
    for (int i = 0, h = (end - begin) / 2; i < h; i++) {
        int tmp = arr[begin + i];
        arr[begin + i] = arr[end - 1 - i];
        arr[end - 1 - i] = tmp;
    }
}

int next_permutation(int *perm, int perm_len)
{
    int i = perm_len - 2;
    for (; i >= 0; i--) {
        if (perm[i] < perm[i + 1]) {
            break;
        }
    }

    if (i < 0) {
        reverse_arr(perm, 0, perm_len);
        return 0;
    }

    int tmp = perm[i];
    int j = perm_len - 1;
    for (; j > i; j--) {
        if (perm[j] > tmp) {
            break;
        }
    }

    swap(int, perm[i], perm[j]);
    reverse_arr(perm, i + 1, perm_len);

    return 1;
}

// num_of_digits is the number of digits of target
// Example: num_of_digits = 3, target = 123 -> digits = {1, 2, 3}
void to_digits(int *digits, int num_of_digits, int target)
{
    for (int i = num_of_digits - 1; i >= 0; i--) {
        digits[i] = target % 10;
        target /= 10;
    }
}

// Example: to_int({9, 6, 7, 8}, 3) = 967
int to_int(const int *digits, int n)
{
    int res = 0;

    for (int i = 0; i < n; i++) {
        res = res * 10 + digits[i];
    }

    return res;
}

void make_sieve(char *sieve, long sieve_len)
{
    if (sieve_len <= 0L) {
        return;
    }

    sieve[0] = 0;

    if (sieve_len == 1L) {
        return;
    }

    sieve[1] = 0;

    for (long i = 2L; i < sieve_len; i++) {
        sieve[i] = 1;
    }
    
    for (long i = 4L; i < sieve_len; i += 2L) {
        sieve[i] = 0;
    }

    for (long i = 3L; i * i < sieve_len; i += 2L) {
        if (sieve[i]) {
            for (long j = i * i; j < sieve_len; j += i) {
                sieve[j] = 0;
            }
        }
    }
}

int main(void)
{
    char prime[LIMIT];
    make_sieve(prime, LIMIT);

    int checked[LIMIT] = {0};

    for (int perm_seed = LIMIT / 10; perm_seed < LIMIT; perm_seed++) {
        if (checked[perm_seed]) {
            continue;
        }

        int digits[NUM_OF_DIGITS];
        to_digits(digits, NUM_OF_DIGITS, perm_seed);

        int buf[BUF_LEN];
        int buf_size = 0;

        do {
            int perm = to_int(digits, NUM_OF_DIGITS);
            checked[perm] = 1;

            if (prime[perm]) {
                buf[buf_size++] = perm;
            }
        } while (next_permutation(digits, NUM_OF_DIGITS));

        // buf[] consists of prime numbers that are strictly monotonically increasing

        for (int i = 0; i < buf_size - 2; i++) {
            int first = buf[i];

            for (int j = i + 1; j < buf_size - 1; j++) {
                int second = buf[j];
                int diff = second - first;

                for (int k = j + 1; k < buf_size; k++) {
                    int third = buf[k];

                    if (third - second == diff) {
                        if (first == 1487 && second == 4817 && third == 8147) {
                            continue;   // We need to find a sequence other than 1487, 4817, 8147
                        }

                        printf("%d%d%d\n", first, second, third);
                        return 0;
                    }
                }
            }
        }
    }

    return 1;   // Will not reach here
}
