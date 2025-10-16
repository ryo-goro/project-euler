// Pentagon Numbers
// 5482660
// p_2167 = 7042750, p_1020 = 1560090
// p_2167 - p_1020 = 5482660 = p_1912, p_2167 + p_1020 = 8602840 = p_2395

#include <stdio.h>

#define INFINITY (1LL << 32)    // Good enough as long as it's >= 5482660

// Returns n * (3 * n - 1) / 2, the n-th pentagonal number
long long pentagonal_number(long long n)
{
    return n * (3 * n - 1) / 2;
}

// Returns the integer part of the square root of n
unsigned long long truncated_sqrt(unsigned long long n)
{
    unsigned long long l = 0;
    unsigned long long r = 1LLU << 32;

    do {
        unsigned long long m = (l + r) / 2;
        if (n < m * m) {
            r = m;
        } else {
            l = m + 1;
        }
    } while (l < r);

    return l - 1;
}

// Note that this function does not consider 0 to be pentagonal
int is_pentagonal(unsigned long long target)
{
    // If target > 0 is pentagonal, there exists an integer n > 0 that fulfills target = n * (3 * n - 1) / 2
    // Solving this quadratic equation for n yields n = (1 + sqrt(1 + 24 * target)) / 6

    unsigned long long radicand = 1 + 24 * target;
    unsigned long long root = truncated_sqrt(radicand);

    return root * root == radicand && (1 + root) % 6 == 0LLU;
}

int main(void)
{
    long long res_diff = INFINITY;
    
    // To verify the minimality of res_diff after we find a candidate,
    // we need to run this loop until there will not be other candidates,
    // that is, until i no longer satisfies p_i - p_{i - 1} < res_diff
    for (long i = 2; /* p_i - p_{i - 1} = */ 3 * i - 2 < res_diff; i++) {
        long long p_i = pentagonal_number(i);

        for (long j = i - 1; j > 0L; j--) {
            long long p_j = pentagonal_number(j);
            long long diff = p_i - p_j;
            long long sum = p_i + p_j;

            if (diff >= res_diff) {
                break;  // No need to continue the "j" loop because diff gets larger as j decrements
            }

            if (is_pentagonal(diff) && is_pentagonal(sum)) {
                res_diff = diff;    // Now diff is a candidate for the answer
                break;  // No need to continue the "j" loop because diff gets larger as j decrements
            }
        }
    }

    printf("%lld\n", res_diff);

    return 0;
}
