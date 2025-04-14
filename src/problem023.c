// Non-Abundant Sums

#include <stdio.h>
#include <stdlib.h>

#define LIMIT 28123

long sum_of_proper_divisors(long n)
{
    if (n <= 1L) {
        return 0L;
    }

    long sum = 1L;
    long d;
    for (d = 2L; d * d < n; d++) {
        if (n % d == 0L) {
            sum += d + n / d;
        }
    }

    if (d * d == n) {
        sum += d;
    }

    return sum;
}

int is_abundant(long n)
{
    return n < sum_of_proper_divisors(n);
}

int main(void)
{
    int abundant[LIMIT];
    int count = 0;

    for (int i = 1; i < LIMIT; i++) {
        if ((abundant[i] = is_abundant(i))) {
            count++;
        }
    }

    int *abundant_nums = (int *)calloc(count, sizeof(int));
    if (abundant_nums == NULL) {
        fprintf(stderr, "Out of memory\n");
        return 1;
    }

    for (int i = 1, idx = 0; i < LIMIT; i++) {
        if (abundant[i]) {
            abundant_nums[idx++] = i;
        }
    }

    int to_be_excluded[LIMIT + 1] = {0};

    for (int i = 0; i < count; i++) {
        int sum = abundant_nums[i] * 2;
        if (sum > LIMIT) {
            break;
        }
        to_be_excluded[sum] = 1;

        for (int j = i + 1; j < count; j++) {
            sum = abundant_nums[i] + abundant_nums[j];
            if (sum > LIMIT) {
                break;
            }
            to_be_excluded[sum] = 1;
        }
    }

    long total = 0;
    for (int i = 0; i <= LIMIT; i++) {
        if (!to_be_excluded[i]) {
            total += i;
        }
    }

    printf("%ld\n", total);

    free(abundant_nums);
    
    return 0;
}
