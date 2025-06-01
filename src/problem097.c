// Large Non-Mersenne Prime

#include <stdio.h>

#define TARGET_COEFFICIENT 28433
#define TARGET_POWER 7830457L
#define BULK_POWER 16
#define NUM_OF_DIGITS 10

void to_array(long *digits, long target)
{
    int n = 0;

    while (target > 0L) {
        digits[n++] = target % 10;
        target /= 10;
    }
}

void multiply(long *digits, int n, long multiplier)
{
    for (int i = 0; i < n; i++) {
        digits[i] *= multiplier;
    }
}

void simplified_carry(long *digits, int n)
{
    for (int i = 0; i < n - 1; i++) {
        digits[i + 1] += digits[i] / 10;
        digits[i] %= 10;
    }

    digits[n - 1] %= 10;
}

int main(void)
{
    long digits[NUM_OF_DIGITS] = {0};
    to_array(digits, TARGET_COEFFICIENT);

    // 28433 * 2^7830457 + 1
    // = 28433 * 2^(16 * (7830457 / 16)) * 2^(7830457 % 16) + 1
    // = 28433 * (2^16)^489403 * 2^9 + 1

    for (long i = 0; i < TARGET_POWER / BULK_POWER; i++) {
        multiply(digits, NUM_OF_DIGITS, 1 << BULK_POWER);
        simplified_carry(digits, NUM_OF_DIGITS);
    }

    multiply(digits, NUM_OF_DIGITS, 1 << (TARGET_POWER % BULK_POWER));
    digits[0] += 1;
    simplified_carry(digits, NUM_OF_DIGITS);

    for (int i = NUM_OF_DIGITS - 1; i >= 0; i--) {
        printf("%ld", digits[i]);
    }
    putchar('\n');

    return 0;
}
