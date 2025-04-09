// Special Pythagorean Triplet

#include <stdio.h>

#define LEN 1000

int main(void)
{
    for (long a = 1; a <= (LEN - 3) / 3; a++) {
        for (long b = a + 1, blim = (LEN - 1 - a) / 2; b <= blim; b++) {
            long c = LEN - a - b;
            if (a * a + b * b == c * c) {
                printf("%ld\n", a * b * c);
                return 0;
            }
        }
    }

    return 0;
}
