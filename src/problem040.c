// Champernowne's Constant

#include <stdio.h>

// Returns the n-th digit of the fractional part of the Champernowne constant
int get_digit(long n)
{
    long power10 = 1L;
    long s = 1L;    // 9 * (1 * 10^0 + 2 * 10^1 + 3 * 10^2 + ...)
    long increment;
    int num_of_digits = 1;

    while (s + (increment = 9 * num_of_digits * power10) <= n) {
        s += increment;
        num_of_digits++;
        power10 *= 10L;
    }

    long target = power10 + (n - s) / num_of_digits;

    for (int i = 1; i < num_of_digits - (int)((n - s) % num_of_digits); i++) {
        target /= 10L;
    }

    return (int)(target % 10L);
}

int main(void)
{
    long power10 = 1L;
    long res = 1L;

    for (int i = 0; i < 7; i++) {
        res *= get_digit(power10);
        power10 *= 10L;
    }
    
    printf("%ld\n", res);

    return 0;
}
