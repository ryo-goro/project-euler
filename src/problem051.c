// Prime Digit Replacements

#include <stdio.h>

#define MAX_NUM_OF_DIGITS 10
#define HIT_THRESHOLD 8

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

// ex. [1, 2, 3, 4] => 1234
long to_long(const int *digits, int num_of_digits)
{
    long res = 0;

    for (int i = 0; i < num_of_digits; i++) {
        res = res * 10 + digits[i];
    }

    return res;
}

// Returns a^n
long power(long a, int n)
{
    long res = a;
    for (int i = 1; i < n; i++) {
        res *= a;
    }

    return res;
}

int main(void)
{
    int digits[MAX_NUM_OF_DIGITS];
    int aster_pos[MAX_NUM_OF_DIGITS - 1];

    long res = -1L;

    for (int num_of_digits = 5; res == -1L; num_of_digits++) {
        for (int num_of_asters = 3; num_of_asters < num_of_digits; num_of_asters += 3) {
            for (int i = 0; i < num_of_asters; i++) {
                aster_pos[i] = 1;
            }
            for (int i = num_of_asters; i < num_of_digits - 1; i++) {
                aster_pos[i] = 0;
            }
            reverse(aster_pos, 0, num_of_digits - 1);

            long power10 = power(10, num_of_digits - 1 - num_of_asters);

            // The rightmost digit must be 1, 3, 5, 7 or 9
            for (int last_digit = 1; last_digit < 10; last_digit += 2) {
                digits[num_of_digits - 1] = last_digit;

                do {
                    for (long fixed_digits = 0; fixed_digits < power10; fixed_digits++) {
                        long tmp = fixed_digits;
                        for (int i = num_of_digits - 2; i >= 0; i--) {
                            if (!aster_pos[i]) {
                                digits[i] = (int)(tmp % 10);
                                tmp /= 10;
                            }
                        }

                        if (!aster_pos[0] && digits[0] == 0) {
                            continue;
                        }

                        long candidate;
                        int aster_digit = aster_pos[0] ? 1 : 0;

                        for (; aster_digit <= 10 - HIT_THRESHOLD; aster_digit++) {
                            for (int i = 0; i < num_of_digits - 1; i++) {
                                if (aster_pos[i]) {
                                    digits[i] = aster_digit;
                                }
                            }

                            long target = to_long(digits, num_of_digits);

                            if (is_prime(target)) {
                                candidate = target;
                                break;
                            }
                        }

                        int miss = aster_digit;

                        // Candidate not found
                        if (miss > 10 - HIT_THRESHOLD) {
                            continue;
                        }

                        for (aster_digit++; aster_digit < 10; aster_digit++) {
                            for (int i = 0; i < num_of_digits - 1; i++) {
                                if (aster_pos[i]) {
                                    digits[i] = aster_digit;
                                }
                            }

                            if (!is_prime(to_long(digits, num_of_digits))) {
                                if (++miss > 10 - HIT_THRESHOLD) {
                                    break;
                                }
                            }
                        }

                        if (miss <= 10 - HIT_THRESHOLD && (res < 0L || res > candidate)) {
                            res = candidate;
                        }
                    }
                } while (next_permutation(aster_pos, num_of_digits - 1));
            }
        }
    }

    printf("%ld\n", res);

    return 0;
}
