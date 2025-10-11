// Champernowne's Constant
// 210

#include <stdio.h>

// Returns a^n
long power(long a, int n)
{
    long res = 1;

    for (int i = 0; i < n; i++) {
        res *= a;
    }

    return res;
}

// Returns the n-th digit of the fractional part of the Champernowne constant
int champernowne_digit(long n)
{
    long power10 = 1;
    long s = 1; // 9 * (1 * 10^0 + 2 * 10^1 + 3 * 10^2 + ...)
    long increment;
    int num_of_digits = 1;

    while (s + (increment = 9 * num_of_digits * power10) <= n) {
        s += increment;
        num_of_digits++;
        power10 *= 10;
    }

    long target = power10 + (n - s) / num_of_digits;

    for (int i = 1; i < num_of_digits - (int)((n - s) % num_of_digits); i++) {
        target /= 10;
    }

    return (int)(target % 10);
}

int main(void)
{
    long res = 1;

    for (int n = 0; n < 7; n++) {
        res *= champernowne_digit(power(10, n));
    }
    
    printf("%ld\n", res);

    return 0;
}
