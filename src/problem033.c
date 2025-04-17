// Digit Cancelling Fractions

#include <stdio.h>

long gcd(long a, long b)
{
    long r;

    while (b > 0L) {
        r = a % b;
        a = b;
        b = r;
    }

    return a;
}

int main(void)
{
    long numerators = 1L;
    long denominators = 1L;
    
    // The target fraction is a / b where 10 <= a < b < 100
    // Let a = 10a2 + a1, b = 10b2 + b1 (a1, b1 != 0)
    // Then the possibilities are:
    // - a1 == b2, and a / b = (10a2 + a1) / (10a1 + b1) = a2 / b1
    // - a2 == b1, and a / b = (10a2 + a1) / (10b2 + a2) = a1 / b2
    for (int a = 10; a < 100; a++) {
        int a1 = a % 10;
        if (a1 == 0) {
            continue;
        }
        int a2 = a / 10;

        for (int b = a + 1; b < 100; b++) {
            int b1 = b % 10;
            if (b1 == 0) {
                continue;
            }
            int b2 = b / 10;

            if ((a1 == b2 && a * b1 == b * a2) || (a2 == b1 && a * b2 == b * a1)) {
                numerators *= a;
                denominators *= b;
            }
        }
    }

    printf("%ld\n", denominators / gcd(denominators, numerators));

    return 0;
}
