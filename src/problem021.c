// Amicable Numbers
// Cache can be used

#include <stdio.h>

#define LIMIT 10000

int sum_of_proper_divisors(int n)
{
    if (n <= 1) {
        return 0;
    }

    int sum = 1;
    int d;
    for (d = 2; d * d < n; d++) {
        if (n % d == 0) {
            sum += d + n / d;
        }
    }

    if (d * d == n) {
        sum += d;
    }

    return sum;
}

int main(void)
{
    int res = 0;

    for (int a = 1; a < LIMIT; a++) {
        int b = sum_of_proper_divisors(a);

        if (a == b) {
            continue;
        }
        
        if (a == sum_of_proper_divisors(b)) {
            res += a;
        }
    }

    printf("%d\n", res);

    return 0;
}
