// Counting Fractions in a Range

#include <stdio.h>

#define MAX_DENOMINATOR 12000

int gcd(int a, int b)
{
    int r;

    do {
        r = a % b;
        a = b;
        b = r;
    } while (b > 0);

    return a;
}

int is_coprime(int a, int b)
{
    return gcd(a, b) == 1;
}

int main(void)
{
    long count = 0;

    for (int q = 2; q <= MAX_DENOMINATOR; q++) {
        // 1/3 < p/q < 1/2 <-> q/3 < p < q/2
        for (int p = q / 3 + 1; p < (q + 1) / 2; p++) {
            if (is_coprime(p, q)) {
                count++;
            }
        }
    }

    printf("%ld\n", count);

    return 0;
}
