// Truncatable Primes
// 748317

#include <stdio.h>

#define LIMIT 11

int is_prime(long target)
{
    if (target < 2L) {
        return 0;
    }

    if (target == 2L) {
        return 1;
    }

    if (target % 2 == 0L) {
        return 0;
    }

    for (long d = 3; d * d <= target; d += 2) {
        if (target % d == 0L) {
            return 0;
        }
    }

    return 1;
}

int is_left_truncatable(long x)
{
    long power10 = 10;

    while (power10 <= x) {
        power10 *= 10;
    }

    while (x > 0L) {
        power10 /= 10;
        if (!is_prime(x)) {
            return 0;
        }
        x %= power10;
    }
    
    return 1;
}

int is_right_truncatable(long x)
{
    while (x > 0L) {
        if (!is_prime(x)) {
            return 0;
        }
        x /= 10;
    }

    return 1;
}

int is_truncatable(long x)
{
    if (!is_left_truncatable(x)) {
        return 0;
    }

    // Whether x is prime or not has already been checked by is_left_truncatable()
    // So we only need to check if x/10 (obtained by truncating x to 1 digit) is right-truncatable
    if (!is_right_truncatable(x / 10)) {
        return 0;
    }

    return 1;
}

int main(void)
{
    int head[] = {7, 5, 3, 2};
    int mid[]  = {9, 7, 3, 1};
    int tail[] = {7, 3};

    int head_max_idx = sizeof(head) / sizeof(head[0]) - 1;
    int mid_max_idx  = sizeof(mid)  / sizeof(mid[0])  - 1;
    int tail_max_idx = sizeof(tail) / sizeof(tail[0]) - 1;

    int stk[64];
    int stk_size = 0;

    long long res = 0LL;

    for (int count = 0, num_of_digits = 2; count < LIMIT; num_of_digits++) {
        long target = head[stk[0] = head_max_idx];
        for (int i = 1; i < num_of_digits - 1; i++) {
            target = target * 10 + mid[stk[i] = mid_max_idx];
        }
        target = target * 10 + tail[stk[num_of_digits - 1] = tail_max_idx];
        if (is_truncatable(target)) {
            count++;
            res += target;
        }

        stk_size = num_of_digits;

        while (stk_size > 0) {
            int tmp = stk[--stk_size];
            target /= 10;

            if (tmp <= 0) {
                continue;
            }

            tmp--;

            if (stk_size == num_of_digits - 1) {
                target = target * 10 + tail[tmp];
                stk[stk_size++] = tmp;
            } else {
                target = target * 10 + ((stk_size == 0) ? head[tmp] : mid[tmp]);
                stk[stk_size++] = tmp;
                while (stk_size < num_of_digits - 1) {
                    target = target * 10 + mid[stk[stk_size++] = mid_max_idx];
                }
                target = target * 10 + tail[stk[stk_size++] = tail_max_idx];
            }

            if (is_truncatable(target)) {
                count++;
                res += target;
            }
        }
    }

    printf("%lld\n", res);

    return 0;
}
