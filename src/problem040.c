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

// Returns the n-th digit of target
// Example: nth_digit(123, 1) = 3
// Example: nth_digit(123, 4) = 0 (the 4th digit of 123 = 0123 is 0)
// target should be >= 0
// If n <= 0, the first (rightmost) digit of target will be returned
int nth_digit(long target, int n)
{
    long pow10 = 1; // 10^{n-1}
    for (int i = 1; i < n; i++) {
        pow10 *= 10;
    }

    return (int)(target / pow10 % 10);
}

// Returns the n-th digit of the fractional part of the Champernowne constant
// n should be > 0
int champernowne_digit(long n)
{
    // Champernowne constant is 0.|123456789|1011...99|100101...999|1000...
    // Let's call the sequence 123456789 the first block, 1011...99 the second block, etc.,
    // and the n-th digit in the fractional part of the Champernowne constant "the target digit"

    // If the target digit is in the m-th block, n and m fulfill s_m <= n < s_{m + 1}, and vice versa,
    // where s_k is the number of digits in the fractional part of the Champernowne constant
    // up to and including the first digit of the k-th block

    int block_num = 1;  // The number of the block where the target digit is in
    long power10 = 1;
    long block_len = 9; // The number of digits in a block

    // The number of digits in the fractional part of the Champernowne constant
    // up to and including the first digit of the `block_num`-th block
    long total_digit_count = 1;

    // Note that the number of digits in the m-th block is 9 * m * 10^{m - 1}
    while (total_digit_count + block_len <= n) {
        total_digit_count += block_len;
        block_num++;
        power10 *= 10;
        block_len = 9 * block_num * power10;
    }

    // Here, power10 = 10^{block_num - 1},
    // and total_digit_count = 1 + 1 * 9 + 2 * 90 + 3 * 900 + ... + 9 * (block_num - 1) * 10^{block_num - 2}
    
    // `target` is a `block_num`-digit number in the `block_num`-th block where the target digit is in
    // Example: If n = 10 or 11, target = 10
    // Example: If n = 190, 191 or 192, target = 100
    // Note that the m-th block consists of m-digit numbers and the block starts from 10^{m - 1}
    long target = power10 + (n - total_digit_count) / block_num;

    return nth_digit(target, block_num - (int)((n - total_digit_count) % block_num));
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
