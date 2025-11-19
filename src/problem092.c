// Square Digit Chains
// 8581146

#include <stdio.h>

#define LEN (9 * 9 * 7 + 1)
#define LIMIT 10000000L // 10 million

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

int compute(long target)
{
    static int digits[10];
    int len = to_digits_rev(digits, target);

    int res = 0;
    for (int i = 0; i < len; i++) {
        res += digits[i] * digits[i];
    }

    return res;
}

int main(void)
{
    int ends[LEN] = {0, 1};
    ends[89] = 89;

    for (int i = 2; i < LEN; i++) {
        int val = i;

        while (val != 1 && val != 89) {
            val = compute(val);
        }

        ends[i] = val;
    }

    long count = 0;

    for (long i = 1; i < LIMIT; i++) {
        if (ends[compute(i)] == 89) {
            count++;
        }
    }

    printf("%ld\n", count);

    return 0;
}
