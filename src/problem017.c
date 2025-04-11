// Number Letter Counts

#include <stdio.h>

const int one_digit[] = {3, 3, 5, 4, 4, 3, 5, 5, 4};        // From one to nine
const int teen[]      = {3, 6, 6, 8, 8, 7, 7, 9, 8, 8};     // From ten to nineteen
const int ty[]        = {6, 6, 5, 5, 5, 7, 6, 6};           // From twenty to ninety

int sumof(const int *a, int n)
{
    int res = 0;

    for (int i = 0; i < n; i++) {
        res += a[i];
    }

    return res;
}

int main(void)
{
    int one_digit_sum = sumof(one_digit, 9);    // 1 ~ 9
    int teen_sum      = sumof(teen, 10);        // 10 ~ 19
    int ty_sum        = sumof(ty, 8);           // 20, 30, ..., 90

    /* 1 ~ 99 */
    int less_than_hundred_sum = 0;
    less_than_hundred_sum += one_digit_sum;                     // 1 ~ 9
    less_than_hundred_sum += teen_sum;                          // 10 ~ 19
    less_than_hundred_sum += ty_sum * 10 + one_digit_sum * 8;   // 20 ~ 99

    /* 1 ~ 1000 */
    int total = one_digit_sum * 100             // Sum for the first digit of x00 ~ x99 (1 <= x <= 9)
                + 7 * 100 * 9                   // hundred
                + 3 * 99 * 9                    // and
                + less_than_hundred_sum * 10    // Sum for the last 2 digits of x01 ~ x99 (0 <= x <= 9)
                + 11;                           // one thousand

    printf("%d\n", total);

    return 0;
}
