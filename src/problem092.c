// Square Digit Chains
// 8581146

#include <stdio.h>

#define LIMIT 10000000L // 10 million
#define MAX_NUM_OF_DIGITS 7
#define LEN (9 * 9 * MAX_NUM_OF_DIGITS + 1)

// Example: target = 123 -> digits = {3, 2, 1} and the function returns 3
int to_digits_rev(int *digits, long target)
{
    int len = 0;

    while (target > 0L) {
        digits[len++] = (int)(target % 10);
        target /= 10;
    }

    return len;
}

int sum_of_squared_digits(long target)
{
    static int digits[64];
    int len = to_digits_rev(digits, target);

    int res = 0;
    for (int i = 0; i < len; i++) {
        res += digits[i] * digits[i];
    }

    return res;
}

int main(void)
{
    // If a positive integer x is < 10^n, sum_of_squared_digits(x) <= 9^2 * n
    // So the strategy is:
    // 1. For each positive integer equal to or less than 9^2 * MAX_NUM_OF_DIGITS,
    //    check if the chain starting with it arrives at 1 or 89, and record the result
    // 2. For each positive integer x less than LIMIT,
    //    calculate sum_of_squared_digits(x) (this value is <= 9^2 * MAX_NUM_OF_DIGITS)
    //    and check the record of that value
    
    int destinations[LEN] = {0, 1};
    destinations[89] = 89;

    int buf[LEN];

    for (int i = 2; i < LEN; i++) {
        int val = i;
        int buf_len = 0;

        while (destinations[val] == 0) {
            buf[buf_len++] = val;
            val = sum_of_squared_digits(val);
        }

        int destination = destinations[val];

        for (int j = 0; j < buf_len; j++) {
            destinations[buf[j]] = destination;
        }
    }

    long count = 0;

    for (long i = 1; i < LIMIT; i++) {
        if (destinations[sum_of_squared_digits(i)] == 89) {
            count++;
        }
    }

    printf("%ld\n", count);

    return 0;
}
