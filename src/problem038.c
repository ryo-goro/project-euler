// Pandigital Multiples

#include <stdio.h>

void clear(int *a, int n)
{
    for (int i = 0; i < n; i++)
        a[i] = 0;
}

int add_digit_counts(int *a, int target)
{
    int count = 0;

    while (target > 0) {
        a[target % 10]++;
        count++;
        target /= 10;
    }

    return count;
}

int is_pandigit(int *a)
{
    if (a[0] > 0) {
        return 0;
    }

    for (int i = 1; i < 10; i++) {
        if (a[i] != 1) {
            return 0;
        }
    }

    return 1;
}

long long concat(long long a, long long b)
{
    long long power10 = 10LL;

    while (power10 <= b) {
        power10 *= 10LL;
    }

    return a * power10 + b;
}

int main(void)
{
    int counts[10] = {0};

    long long res = 918273645;  // Concatenated product of 9 and (1, 2, 3, 4, 5)

    // If the concatenated product of x and (1, 2, ..., n) (n > 1) is the maximum value:
    // - The leftmost digit of x must be 9
    // - x has at most 4 digits
    for (int right = 0; right < 1000; right++) {
        int target = (int)concat(9, right);
        long long candidate = 0LL;

        clear(counts, 10);

        int total_count = 0;

        for (int n = 1; ; n++) {
            total_count += add_digit_counts(counts, target * n);
            candidate = concat(candidate, target * n);
            if (total_count >= 9) {
                break;
            } 
        }

        if (total_count != 9) {
            continue;
        }

        if (is_pandigit(counts) && candidate > res) {
            res = candidate;
        }
    }

    printf("%lld\n", res);

    return 0;
}
