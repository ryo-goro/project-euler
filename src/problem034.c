// Digit Factorials
// 40730

#include <stdio.h>

int main(void)
{
    long factorial[10] = {1};
    for (int i = 1; i < 10; i++) {
        factorial[i] = factorial[i - 1] * i;
    }

    long long total = 0;

    // Let x an n-digit integer (n >= 2) which can be written as the sum of the factorial of its digits
    // Then 10^(n-1) <= x <= n * 9! = 362880n
    // Only n = 2, 3, 4, 5, 6, 7 hold this condition
    // So 10 <= x <= 362880 * 7 = 2540160
    for (long x = 10, limit = factorial[9] * 7; x <= limit; x++) {
        long sum = 0;
        long y = x;

        do {
            sum += factorial[y % 10];
            y /= 10;
        } while (y > 0L);
        
        if (sum == x) {
            total += x;
        }
    }
    
    printf("%lld\n", total);

    return 0;
}
