// Square Root Convergents

// Let us define a sequence {a_n} by the following recurrence relation:
//
// - a_0 = 1
// - a_(n + 1) = 1 + 1 / (a_n + 1) (n >= 0)
// 
// Then a_n (n >= 1) is the n-th expansion of the infinite continued fraction of the square root of 2
//
// Let us define the natural number sequences {p_n} and {q_n} by the following recurrence relations:
// 
// - p_0 = q_0 = 1
// - p_(n + 1) = p_n + q_n (n >= 0)
// - q_(n + 1) = 2 * p_n + q_n (= p_n + p_(n + 1)) (n >= 0)
// 
// Then the followings hold:
// 
// 1. p_n and q_n are coprime (n >= 0)
// 2. a_n = q_n / p_n (n >= 0)

#include <stdio.h>

#define MAX_ITERATIONS      1000
#define MAX_NUM_OF_DIGITS   1024

#define swap(type, x, y)    do { type t = x; x = y; y = t; } while (0)

void add(int *dst, const int *src, int src_len)
{
    for (int i = 0; i < src_len; i++) {
        dst[i] += src[i];
    }
}

int carry(int *digits, int num_of_digits)
{
    for (int i = 0; i < num_of_digits - 1; i++) {
        digits[i + 1] += digits[i] / 10;
        digits[i] %= 10;
    }

    int top = digits[num_of_digits - 1];

    if (top < 10) {
        return num_of_digits;
    }

    do {
        digits[num_of_digits++ - 1] = top % 10;
        top /= 10;
    } while (top >= 10);

    digits[num_of_digits - 1] = top;

    return num_of_digits;
}

int main(void)
{
    int buf1[MAX_NUM_OF_DIGITS] = {1};
    int buf2[MAX_NUM_OF_DIGITS] = {1};

    int *denominator = buf1;
    int *numerator = buf2;

    int denominator_len = 1;
    int numerator_len = 1;

    int count = 0;

    for (int rep = 0; rep < MAX_ITERATIONS; rep++) {
        swap(int *, denominator, numerator);
        swap(int, denominator_len, numerator_len);

        add(denominator, numerator, numerator_len);
        denominator_len = carry(denominator, denominator_len);

        add(numerator, denominator, denominator_len);
        numerator_len = carry(numerator, denominator_len);

        if (numerator_len > denominator_len) {
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}
