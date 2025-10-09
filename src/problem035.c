// Circular Primes
// 55

#include <stdio.h>

#define LIMIT 1000000L  // 1 million
#define DIGITS_LIMIT 6

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

void insertion_sort(long *arr, int n)
{
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i - 1]) {
            long tmp = arr[i];
            int j = i;

            do {
                arr[j] = arr[j - 1];
                j--;
            } while (j > 0 && tmp < arr[j - 1]);

            arr[j] = tmp;
        }
    }
}

int compress_sorted_arr(long *sorted_arr, int n)
{
    if (n <= 0) {
        return 0;
    }

    long target = sorted_arr[0];
    int len = 1;

    for (int i = 1; i < n; i++) {
        if (target != sorted_arr[i]) {
            sorted_arr[len++] = target = sorted_arr[i];
        }
    }

    return len;
}

// `pow10` should be 10^n where n is the number of digits of `target` including leading 0s
// ex. rotate(123, 100) = 231
// ex. rotate(3051, 1000) = (0)513
// ex. rotate(513, 1000) = rotate((0)513, 1000) = 5130
long rotate(long target, long pow10)
{
    return target % pow10 * 10 + target / pow10;
}

// Returns a^n
// n should be >= 0
long power(long a, int n)
{
    long res = 1;

    for (int i = 0; i < n; i++) {
        res *= a;
    }

    return res;
}

int main(void)
{
    char prime[LIMIT];
    make_sieve(prime, LIMIT);

    int res = 0;
    int checked[LIMIT] = {0};

    // Check 1-digit numbers
    for (int i = 0; i < 10; i++) {
        checked[i] = 1;
        if (prime[i]) {
            res++;
        }
    }

    // The units digit of a prime number with two or more digits is either 1, 3, 7, or 9
    // So the digits of any circular prime number with two or more digits are either 1, 3, 7, or 9
    int digits[] = {1, 3, 7, 9};
    int num_of_digits = sizeof(digits) / sizeof(digits[0]);

    for (int digit_count = 2; digit_count <= DIGITS_LIMIT; digit_count++) {
        long pow10 = power(10, digit_count - 1);
        long rotations[DIGITS_LIMIT];

        // Check `digit_count`-digit numbers
        // Note that the number of those numbers is 4^digit_count,
        // as the digits of the numbers are either 1, 3, 7, or 9
        for (long seed = 0, limit = power(num_of_digits, digit_count); seed < limit; seed++) {
            long tmp_seed = seed;
            long target = 0;

            // Convert seed to target
            // ex. digit_count = 3, seed = 0 = 000 (in base 4) -> target = 111
            // ex. digit_count = 4, seed = 27 = 0123 (in base 4) -> target = 9731
            for (int i = 0; i < digit_count; i++) {
                target = target * 10 + digits[tmp_seed % num_of_digits];
                tmp_seed /= num_of_digits;
            }

            if (checked[target]) {
                continue;
            }
            
            // Collect all the rotations of target
            rotations[0] = target;
            for (int i = 1; i < digit_count; i++) {
                rotations[i] = rotate(rotations[i - 1], pow10);
            }

            // Remove duplication
            insertion_sort(rotations, digit_count);
            int unique_count = compress_sorted_arr(rotations, digit_count);

            // Mark all the rotations of target as checked
            for (int i = 0; i < unique_count; i++) {
                checked[rotations[i]] = 1;
            }

            // Check if all the rotations of target are prime
            int found = 1;
            for (int i = 0; i < unique_count; i++) {
                if (!prime[rotations[i]]) {
                    found = 0;
                    break;
                }
            }
            if (found) {
                res += unique_count;
            }
        }
    }

    printf("%d\n", res);

    return 0;
}
