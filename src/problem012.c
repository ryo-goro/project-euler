// Highly Divisible Triangular Number

#include <stdio.h>

#define THRESHOLD 500
#define ARRAY_LEN 10000

// odd_num should be an odd number > 1
int compute_num_of_divisors(int odd_num)
{
    int res = 2;

    int d = 3;
    for (; d * d < odd_num; d += 2)
        if (odd_num % d == 0)
            res += 2;
    
    if (d * d == odd_num)
        res++;
    
    return res;
}

int main(void)
{
    // cache[i] = the number of positive divisors of 2i+1
    int cache[ARRAY_LEN];
    cache[0] = 1;

    int n = 1;
    int odd = 1;

    while (1) {
        int m = n;
        int factor2 = 1;

        while (m % 2 == 0) {
            m /= 2;
            factor2++;
        }

        int p = factor2 * cache[m / 2];
        int num_of_divisors = p * cache[odd / 2];

        if (num_of_divisors > THRESHOLD) {
            break;
        }

        odd += 2;
        num_of_divisors = p * (cache[odd / 2] = compute_num_of_divisors(odd));

        if (num_of_divisors > THRESHOLD) {
            break;
        }

        n++;
    }

    printf("%ld\n", ((long)n) * odd);

    return 0;
}
