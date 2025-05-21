// Ordered Fractions
// 428570 / 999997

#include <stdio.h>

#define MAX_DENOMINATOR     1000000LU   // 1 million
#define TARGET_NUMERATOR    3
#define TARGET_DENOMINATOR  7

unsigned long gcd(unsigned long a, unsigned long b)
{
    unsigned long r;

    do {
        r = a % b;
        a = b;
        b = r;
    } while (b);

    return a;
}

int main(void)
{
    unsigned long numerator   = 1;
    unsigned long denominator = TARGET_DENOMINATOR;

    // p / q < 3 / 7 -> p < 3 * q / 7 <= 3 * 1000000 / 7
    for (unsigned long p = 1; p < TARGET_NUMERATOR * MAX_DENOMINATOR / TARGET_DENOMINATOR; p++) {
        // p / q < 3 / 7 <-> q > p * 7 / 3
        unsigned long q = p * 7 / 3 + 1;

        if ((long long)p * denominator > (long long)numerator * q) {
            denominator = q;
            numerator = p;
        }
    }

    printf("%lu\n", numerator / gcd(numerator, denominator));

    return 0;
}
