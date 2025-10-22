// Prime Digit Replacements
// 121313
// *2*3*3 yields 121313, 222323, 323333, 424343, 525353, 626363, 828383, and 929393

#include <stdio.h>

#define MAX_NUM_OF_DIGITS 10    // Good enough as long as it's >= the number of digits of the answer
#define HIT_THRESHOLD 8
#define MAX_MISS_COUNT (10 - HIT_THRESHOLD)

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

// Example: to_long({9, 6, 7, 8}, 3) = 967
long to_long(const int *digits, int n)
{
    long res = 0;

    for (int i = 0; i < n; i++) {
        res = res * 10 + digits[i];
    }

    return res;
}

// Returns a^n
long power(long a, int n)
{
    long res = 1;

    for (int i = 0; i < n; i++) {
        res *= a;
    }

    return res;
}

void fill_arr(int *arr, int begin, int end, int value)
{
    for (int i = begin; i < end; i++) {
        arr[i] = value;
    }
}

int main(void)
{
    int digits[MAX_NUM_OF_DIGITS];
    int is_asterisk[MAX_NUM_OF_DIGITS - 1];

    int last_digits[] = {1, 3, 7, 9};
    int num_of_last_digits = sizeof(last_digits) / sizeof(last_digits[0]);

    long res = -1;

    // The flow of the code is as follows:
    // 1. Determine the number of digits to investigate
    // 2. Determine the number of *
    // 3. Determine the positions of *
    // 4. Determine the last digit
    // 5. Determine the digits except *
    // 6. Substitute digits for *

    // 1. Determine the number of digits to investigate
    // It should be > the number of * because the last (rightmost) digit of a family must not be *
    for (int num_of_digits = 4; ; num_of_digits++) {
        // 2. Determine the number of *

        // Let s the sum of the fixed digits of a family, and let n the number of *
        // Example: for 56**3, s = 14 and n = 2
        // Then the sum of the digits of numbers the family yields can be expressed as s + kn (0 <= k <= 9)
        // If n is not a multiple of 3, s + kn is divisible by 3 for at least 3 values of k
        // Considering this fact and the value of HIT_THRESHOLD, we see that n, the number of *, should be a multiple of 3

        // The number of * should be less than the number of digits of the answer because the last (rightmost) digit must not be *

        for (int num_of_asterisks = 3; num_of_asterisks < num_of_digits; num_of_asterisks += 3) {
            int num_of_fixed_digits = num_of_digits - 1 - num_of_asterisks;

            // is_asterisk = {0, 0, ..., 0, 1, 1, ..., 1} (num_of_fixed_digits 0s and num_of_asterisks 1s)
            fill_arr(is_asterisk, 0, num_of_fixed_digits, 0);
            fill_arr(is_asterisk, num_of_fixed_digits, num_of_digits - 1, 1);

            long pow10 = power(10, num_of_fixed_digits);

            // 3. Determine the positions of *
            do {
                // 4. Determine the last digit
                // The last (rightmost) digit must not be *, and it should be either 1, 3, 7 or 9
                for (int last_digit_idx = 0; last_digit_idx < num_of_last_digits; last_digit_idx++) {
                    digits[num_of_digits - 1] = last_digits[last_digit_idx];

                    // 5. Determine the digits except *
                    for (long fixed_digits = 0; fixed_digits < pow10; fixed_digits++) {
                        // Because the number of * is a multiple of 3, if the sum of the digits except * is also a multiple of 3,
                        // all numbers the family yields are divisible by 3, in which case we can skip
                        if ((fixed_digits + last_digits[last_digit_idx]) % 3 == 0) {
                            continue;
                        }

                        // Fill the blanks of digits except * and the last digit
                        long tmp = fixed_digits;
                        for (int i = num_of_digits - 2; i >= 0; i--) {
                            if (!is_asterisk[i]) {
                                digits[i] = (int)(tmp % 10);
                                tmp /= 10;
                            }
                        }

                        // The first (leftmost) digit should be non-zero
                        if (!is_asterisk[0] && digits[0] == 0) {
                            continue;
                        }

                        // 6. Substitute digits for *

                        long candidate = -1;
                        int asterisk_digit = is_asterisk[0] ? 1 : 0;    // The first digit should be non-zero

                        // Find a candidate, the smallest prime number of a family
                        for (; asterisk_digit <= MAX_MISS_COUNT; asterisk_digit++) {
                            // Complete digits by substituting a concrete digit for *
                            for (int i = 0; i < num_of_digits - 1; i++) {
                                if (is_asterisk[i]) {
                                    digits[i] = asterisk_digit;
                                }
                            }

                            long target = to_long(digits, num_of_digits);

                            if (is_prime(target)) {
                                candidate = target;
                                break;
                            }
                        }

                        // Candidate not found
                        if (candidate < 0L) {
                            continue;
                        }

                        int miss_count = asterisk_digit;
                        asterisk_digit++;

                        // Check if the family has the required property
                        for (; asterisk_digit < 10; asterisk_digit++) {
                            // Complete digits by substituting a concrete digit for *
                            for (int i = 0; i < num_of_digits - 1; i++) {
                                if (is_asterisk[i]) {
                                    digits[i] = asterisk_digit;
                                }
                            }

                            if (!is_prime(to_long(digits, num_of_digits))) {
                                miss_count++;

                                if (miss_count > MAX_MISS_COUNT) {
                                    break;
                                }
                            }
                        }

                        if (miss_count <= MAX_MISS_COUNT && (res < 0L || res > candidate)) {
                            res = candidate;
                        }
                    }
                }
            } while (next_permutation(is_asterisk, num_of_digits - 1));
        }

        if (res > 0L) {
            break;
        }
    }

    printf("%ld\n", res);

    return 0;
}
