// Pandigital Multiples
// 932718654

#include <stdio.h>

int num_of_digits(long long target)
{
    int len = 1;
    long long pow10 = 10;

    while (target >= pow10) {
        len++;
        pow10 *= 10;
    }

    return len;
}

// Returns 1 if x is a 1 to 9 pandigital 9-digit number
// Returns 0 otherwise
int is_pandigital(long long x)
{
    int counts[10] = {0};

    while (x > 0LL) {
        counts[(int)(x % 10)]++;
        x /= 10;
    }

    if (counts[0] > 0) {
        return 0;
    }

    for (int i = 1; i < 10; i++) {
        if (counts[i] != 1) {
            return 0;
        }
    }

    return 1;
}

// ex. concat(12, 345) = 12345
// ex. concat(1000, 0) = 10000
long long concat(long long a, long long b)
{
    long long pow10 = 10;

    while (pow10 <= b) {
        pow10 *= 10;
    }

    return a * pow10 + b;
}

int main(void)
{
    // Concatenated product of 9 and (1, 2, 3, 4, 5)
    // The result must be equal to or more than this value
    long long res = 918273645LL;

    // If the concatenated product of x and (1, 2, ..., n) (n > 1) is the maximum value:
    // - The leftmost digit of x is 9
    // - x has at most 4 digits
    // - x does not have 0 as any of its digits
    for (int right = 1; right < 1000; right++) {
        // ex. right = 123 -> x = 9123
        int x = (int)concat(9, right);
        long long candidate = x;

        for (int n = 2; ; n++) {
            candidate = concat(candidate, x * n);
            if (num_of_digits(candidate) >= 9) {
                break;
            } 
        }

        if (candidate > res && is_pandigital(candidate)) {
            res = candidate;
        }
    }

    printf("%lld\n", res);

    return 0;
}
