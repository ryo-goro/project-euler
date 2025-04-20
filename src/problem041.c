// Pandigital Prime

#include <stdio.h>

#define swap(type, x, y)    do { type t = x; x = y; y = t; } while (0)

void reverse(int *a, int l, int r)
{
    for (int i = 0, h = (r - l) / 2; i < h; i++) {
        swap(int, a[l + i], a[r - 1 - i]);
    }
}

int next_permutation_desc(int *a, int n)
{
    int i = n - 2;
    for (; i >= 0; i--) {
        if (a[i] > a[i + 1]) {
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
        if (a[j] < tmp) {
            break;
        }
    }

    swap(int, a[i], a[j]);
    reverse(a, i + 1, n);

    return 1;
}

long to_long(const int *digits, int n)
{
    long res = digits[0];
    for (int i = 1; i < n; i++) {
        res = res * 10 + digits[i];
    }

    return res;
}

int is_prime(long n)
{
    if (n < 2L) {
        return 0;
    }

    if (n == 2L) {
        return 1;
    }

    if (n % 2L == 0L) {
        return 0;
    }

    for (long d = 3L; d * d <= n; d += 2L) {
        if (n % d == 0L) {
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    long res, candidate;
    // By checking whether the sum of each digit is divisible by 3,
    // we see that only 4- or 7-digit pandigital numbers can be prime

    // Scan 4-digit pandigital numbers in descending order
    int a[] = {4, 3, 2, 1};
    do {
        candidate = to_long(a, 4);
        if (is_prime(candidate)) {
            res = candidate;
            break;
        }
    } while (next_permutation_desc(a, 4));

    // Scan 7-digit pandigital numbers in descending order
    int b[] = {7, 6, 5, 4, 3, 2, 1};
    do {
        candidate = to_long(b, 7);
        if (is_prime(candidate)) {
            res = candidate;
            break;
        }
    } while (next_permutation_desc(b, 7));

    printf("%ld\n", res);

    return 0;
}
