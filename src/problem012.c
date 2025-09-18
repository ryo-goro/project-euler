// Highly Divisible Triangular Number
// 76576500

#include <stdio.h>

#define THRESHOLD 500
#define CACHE_LEN 10000

// odd_num must be an odd number that is > 1
// However, this code does not include validation in order to optimize performance
int compute_num_of_divisors(int odd_num)
{
    int res = 2;

    int d = 3;
    for (; d * d < odd_num; d += 2) {
        if (odd_num % d == 0) {
            res += 2;
        }
    }
    
    if (d * d == odd_num) {
        res++;
    }
    
    return res;
}

// num must be positive
// However, this code does not include validation in order to optimize performance
int compute_num_of_divisors_with_cache(int num)
{
    // cache[i] = the number of positive divisors of 2i+1
    static int cache[CACHE_LEN] = {1};

    int exponent_of_2_plus_1 = 1;

    while (num % 2 == 0) {
        num /= 2;
        exponent_of_2_plus_1++;
    }

    // Here num is odd, so it can be represented as num = 2n+1
    int n = num / 2;

    if (n < CACHE_LEN) {
        if (cache[n] == 0) {
            cache[n] = compute_num_of_divisors(num);
        }
        return cache[n] * exponent_of_2_plus_1;
    }
    
    return compute_num_of_divisors(num) * exponent_of_2_plus_1;
}

int main(void)
{
    // Let t(n) be the n-th triangle number, that is, t(n) = 1/2 * n * (n + 1)
    // - t(2n - 1) = n(2n - 1)
    // - t(2n)     = n(2n + 1)

    int n = 1;
    int odd = 1;    // Either 2n - 1 or 2n + 1 for each repetition

    for (;; n++) {
        int num_of_divisors_n = compute_num_of_divisors_with_cache(n);
        int num_of_divisors = num_of_divisors_n * compute_num_of_divisors_with_cache(odd);

        if (num_of_divisors > THRESHOLD) {
            // t(2n - 1) exceeds the threshold
            break;
        }

        odd += 2;
        num_of_divisors = num_of_divisors_n * compute_num_of_divisors_with_cache(odd);

        if (num_of_divisors > THRESHOLD) {
            // t(2n) exceeds the threshold
            break;
        }
    }

    printf("%ld\n", ((long)n) * odd);

    return 0;
}
