// Amicable Numbers
// 31626

#include <stdio.h>

#define LIMIT 10000

// A CACHE_LEN of 10000 results in 8156 hits per 19994 requests (the number of requests made by the for loop in the main function)
// A CACHE_LEN of 100000 results in a similar number of hits (8220) per 19994 requests 
// So a CACHE_LEN of 10000 is enough
#define CACHE_LEN LIMIT

// n should be > 1
int sum_of_proper_divisors(int n)
{
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

// n should be > 1
int sum_of_proper_divisors_with_cache(int n)
{
    static int cache[CACHE_LEN] = {0};

    if (n < CACHE_LEN && cache[n] > 0) {
        return cache[n];
    }

    int res = sum_of_proper_divisors(n);

    if (n < CACHE_LEN) {
        cache[n] = res;
    }

    return res;
}

int main(void)
{
    int res = 0;

    for (int a = 1; a < LIMIT; a++) {
        int b = sum_of_proper_divisors_with_cache(a);

        if (a == b) {
            continue;
        }
        
        if (a == sum_of_proper_divisors_with_cache(b)) {
            res += a;
        }
    }

    printf("%d\n", res);

    return 0;
}
