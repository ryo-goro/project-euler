// Pentagon Numbers

#include <stdio.h>

#define LIMIT 3000

long long pentagon_number(int n)
{
    return (long long)n * (3 * n - 1) / 2;
}

int is_pentagonal(long long n)
{
    int l = 1;
    int r = 2;

    while (pentagon_number(r - 1) < n) {
        r *= 2;
    }

    int m;
    long long p;

    do {
        m = (l + r) / 2;
        if (pentagon_number(m) >= n) {
            r = m;
        } else {
            l = m + 1;
        }
    } while (l < r);

    return n == pentagon_number(l);
}

int main(void)
{
    long long pentagon_numbers[LIMIT];

    for (int i = 1; i < LIMIT; i++)
        pentagon_numbers[i] = pentagon_number(i);
    
    int found = 0;
    long long res = -1LL;

    for (int i = 2; i < LIMIT; i++) {
        long long p_i = pentagon_numbers[i];
        for (int j = 1; j < i; j++) {
            long long p_j = pentagon_numbers[j];
            if (is_pentagonal(p_i - p_j) && is_pentagonal(p_i + p_j)) {
                res = p_i - p_j;
                break;
            }
        }
        if (res > 0LL) {
            break;
        }
    }

    printf("%lld\n", res);

    // int found = 0;
    // long long min;
    // for (int idx = 1; ; idx++) {
    //     min = pentagon_number(idx);

    //     for (int i = idx + 1;; i++) {
    //         long long p = pentagon_number(i);
    //         long long pp = pentagon_number(i - 1);
    //         if (p - pp > min) {
    //             break;
    //         }
    //         if (p - pp == min) {
    //             found = is_pentagonal(p + pp);
    //             break;
    //         }

    //         for (int j = i - 2; j > 0; j--) {
    //             pp = pentagon_number(j);
    //             if (p - pp > min) {
    //                 break;
    //             }
    //             if (p - pp == min) {
    //                 found = is_pentagonal(p + pp);
    //                 break;
    //             }
    //         }
    //         if (found) {
    //             break;
    //         }
    //     }

    //     if (found) {
    //         break;
    //     }
    // }

    // printf("%lld\n", min);

    return 0;
}
