// Square Root Digital Expansion
// https://ja.wikipedia.org/wiki/%E9%96%8B%E5%B9%B3%E6%B3%95

#include <stdio.h>
#include <stdlib.h>

#define N 100U
#define MAX_NUM_OF_DECIMAL_DIGITS 99U

unsigned sum_of_arr(const unsigned *arr, unsigned n)
{
    unsigned res = 0;
    for (unsigned i = 0; i < n; i++) {
        res += arr[i];
    }

    return res;
}

void shift(unsigned *arr, unsigned n, unsigned amount_of_shift)
{
    for (int i = n - 1; i >= 0; i--) {
        arr[i + amount_of_shift] = arr[i];
    }
    for (int i = 0; i < amount_of_shift; i++) {
        arr[i] = 0;
    }
}

void multiply(unsigned *arr, unsigned n, unsigned multiplier)
{
    for (unsigned i = 0; i < n; i++) {
        arr[i] *= multiplier;
    }
}

unsigned carry(unsigned *arr, unsigned arr_len)
{
    for (unsigned i = 1; i < arr_len; i++) {
        arr[i] += arr[i - 1] / 10;
        arr[i - 1] %= 10;
    }

    unsigned rightmost_idx = arr_len - 1;

    while (arr[rightmost_idx] >= 10U) {
        arr[rightmost_idx + 1] = arr[rightmost_idx] / 10;
        arr[rightmost_idx++] %= 10;
    }

    return rightmost_idx + 1;
}

unsigned subtract_digits(unsigned *left_operand, const unsigned *right_operand, unsigned left_operand_len, unsigned right_operand_len)
{
    unsigned carry = 0;
    for (unsigned i = 0; i < right_operand_len; i++) {
        if (left_operand[i] >= right_operand[i] + carry) {
            left_operand[i] -= right_operand[i] + carry;
            carry = 0;
        } else {
            left_operand[i] += 10 - (right_operand[i] + carry);
            carry = 1;
        }
    }

    for (unsigned i = right_operand_len; carry; i++) {
        if (left_operand[i]) {
            left_operand[i] -= carry;
            carry = 0;
        } else {
            left_operand[i] += 10 - carry;
            carry = 1;
        }
    }

    for (unsigned i = left_operand_len; i > 0U; i--) {
        if (left_operand[i - 1]) {
            return i;
        }
    }

    return 1;
}

int compare_digits(const unsigned *left_operand, const unsigned *right_operand, unsigned left_operand_len, unsigned right_operand_len)
{
    if (left_operand_len < right_operand_len) {
        return -1;
    }

    if (left_operand_len > right_operand_len) {
        return 1;
    }

    // left_operand_len == right_operand_len
    for (int i = left_operand_len - 1; i >= 0; i--) {
        if (left_operand[i] < right_operand[i]) {
            return -1;
        }

        if (left_operand[i] > right_operand[i]) {
            return 1;
        }
    }

    return 0;
}

unsigned to_digits(unsigned *digits, unsigned long target)
{
    unsigned len = 0;

    do {
        digits[len++] = target % 10;
        target /= 10;
    } while (target);

    return len;
}

unsigned long truncated_sqrt(unsigned long n)
{
    unsigned long l = 0;
    unsigned long r = 1LU << 16;

    unsigned long m;

    do {
        m = (l + r) / 2;
        if (n < m * m) {
            r = m;
        } else {
            l = m + 1;
        }
    } while (l < r);

    return l - 1;
}

unsigned long expand_sqrt(unsigned *decimal_part, unsigned decimal_part_len, unsigned long target)
{
    unsigned long integer_part = truncated_sqrt(target);

    if (integer_part * integer_part == target) {
        for (unsigned i = 0; i < decimal_part_len; i++) {
            decimal_part[i] = 0;
        }
        return integer_part;
    }

    if (decimal_part_len == 0U) {
        return integer_part;
    }

    unsigned m = 1; // Number of digits of `integer_part`
    
    for (unsigned long power10 = 1; m < 10; m++) {
        power10 *= 10;
        if (integer_part < power10) {
            break;
        }
    }

    unsigned *q = calloc(m + 2 * decimal_part_len, sizeof(unsigned));
    unsigned *x = calloc(m + 2 * decimal_part_len, sizeof(unsigned));
    unsigned *r = calloc(m + 2 * decimal_part_len, sizeof(unsigned));

    unsigned q_len = to_digits(q, 2 * integer_part);
    unsigned x_len = to_digits(x, target);
    unsigned r_len = to_digits(r, integer_part * integer_part);

    for (unsigned n = 0; n < decimal_part_len; n++) {
        x_len = subtract_digits(x, r, x_len, r_len);
        shift(x, x_len, 2);
        x_len += 2;

        unsigned a;
        for (a = 9; a >= 1; a--) {
            r[0] = a;
            for (unsigned i = 0; i < q_len; i++) {
                r[i + 1] = q[i];
            }
            multiply(r, q_len + 1, a);
            r_len = carry(r, q_len + 1);

            // r vs x
            if (compare_digits(r, x, r_len, x_len) < 0) {
                break;
            }
        }

        if (a == 0U) {
            r[0] = 0;
            r_len = 1;
        }

        decimal_part[n] = a;

        shift(q, q_len, 1);
        q[0] = 2 * a;
        q_len = carry(q, q_len + 1);
    }

    free(r);
    free(x);
    free(q);

    return integer_part;
}

int main(void)
{
    unsigned decimal_part[MAX_NUM_OF_DECIMAL_DIGITS];
    unsigned long res = 0;

    for (unsigned n = 1; n <= N; n++) {
        unsigned long integer_part = expand_sqrt(decimal_part, MAX_NUM_OF_DECIMAL_DIGITS, n);
        if (integer_part * integer_part == n) {
            continue;
        }

        res += integer_part + sum_of_arr(decimal_part, MAX_NUM_OF_DECIMAL_DIGITS);
    }
    
    printf("%lu\n", res);

    return 0;
}
