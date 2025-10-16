// Triangular, Pentagonal, and Hexagonal
// 1533776805

#include <stdio.h>

// Returns n * (2 * n - 1), the n-th hexagonal number
long long hexagonal_number(long long n)
{
    return n * (2 * n - 1);
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
    // t(n) = n * (n + 1) / 2
    // p(n) = n * (3 * n - 1) / 2
    // h(n) = n * (2 * n - 1)

    // Note that all hexagonal numbers are triangle:
    // t(2 * n - 1) = (2 * n - 1) * (2 * n - 1 + 1) / 2 = n * (2 * n - 1) = h(n)

    long long res;

    // t(285) = p(165) = h(143) = 40755
    // We need to find the next triangle number that is also pentagonal and hexagonal
    for (long n = 144; ; n++) {
        res = hexagonal_number(n);
        
        if (is_pentagonal(res)) {
            break;
        }
    }

    printf("%lld\n", res);

    return 0;
}
