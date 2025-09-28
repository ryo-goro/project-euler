// Non-Abundant Sums
// 4179871

#include <stdio.h>
#include <stdlib.h>

#define LIMIT 28123 // All integers greater than this limit can be written as the sum of two abundant numbers

// n should be > 1
long sum_of_proper_divisors(long n)
{
    long sum = 1;
    long d;

    for (d = 2; d * d < n; d++) {
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
    int abundant[LIMIT] = {0};
    int num_of_abundant_nums = 0;

    for (int i = 2; i < LIMIT; i++) {
        if ((abundant[i] = is_abundant(i))) {
            num_of_abundant_nums++;
        }
    }

    int *abundant_nums = (int *)calloc(num_of_abundant_nums, sizeof(int));

    for (int i = 1, idx = 0; i < LIMIT; i++) {
        if (abundant[i]) {
            abundant_nums[idx++] = i;
        }
    }

    // to_be_excluded[n] == 1 if n can be written as the sum of two abundant numbers
    // to_be_excluded[n] == 0 otherwise
    int to_be_excluded[LIMIT + 1] = {0};

    for (int i = 0; i < num_of_abundant_nums; i++) {
        int abundant_num_base = abundant_nums[i];
        int j;

        for (j = i; j < num_of_abundant_nums; j++) {
            int sum = abundant_num_base + abundant_nums[j];

            if (sum > LIMIT) {
                break;
            }

            to_be_excluded[sum] = 1;
        }
        
        if (j == i) {
            break;
        }
    }

    long total = 0;

    for (int i = 0; i <= LIMIT; i++) {
        if (to_be_excluded[i]) {
            continue;
        }

        total += i;
    }

    printf("%ld\n", total);

    free(abundant_nums);
    
    return 0;
}
