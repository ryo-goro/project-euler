// Sub-string Divisibility

#include <stdio.h>

#define swap(type, x, y)    do { type t = x; x = y; y = t; } while (0)

void reverse(int *a, int l, int r)
{
    for (int i = 0, h = (r - l) / 2; i < h; i++) {
        swap(int, a[l + i], a[r - 1 - i]);
    }
}

int next_permutation(int *a, int n)
{
    int i = n - 2;
    for (; i >= 0; i--) {
        if (a[i] < a[i + 1]) {
            break;
        }
    }

    if (i < 0) {
        reverse(a, 0, n);
        return 0;
    }

    int tmp = a[i];
    int j = n - 1;
    for (; j > i; j--) {
        if (a[j] > tmp) {
            break;
        }
    }

    swap(int, a[i], a[j]);
    reverse(a, i + 1, n);

    return 1;
}

long to_ll(const int *digits, int n)
{
    long long res = digits[0];
    for (int i = 1; i < n; i++) {
        res = res * 10 + digits[i];
    }

    return res;
}

int main(void)
{
    int digits[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    long long res = 0LL;

    do {
        if (digits[0] == 0) {
            continue;
        }

        if (digits[3] % 2 != 0) {
            continue;
        }

        if ((digits[2] + digits[3] + digits[4]) % 3 != 0) {
            continue;
        }

        if (digits[5] != 0 && digits[5] != 5) {
            continue;
        }

        if ((100 * digits[4] + 10 * digits[5] + digits[6]) % 7 != 0) {
            continue;
        }

        if ((100 * digits[5] + 10 * digits[6] + digits[7]) % 11 != 0) {
            continue;
        }

        if ((100 * digits[6] + 10 * digits[7] + digits[8]) % 13 != 0) {
            continue;
        }

        if ((100 * digits[7] + 10 * digits[8] + digits[9]) % 17 != 0) {
            continue;
        }

        res += to_ll(digits, 10);
    
    } while (next_permutation(digits, 10));

    printf("%lld\n", res);

    return 0;
}
