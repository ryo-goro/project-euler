// Pandigital Products

#include <stdio.h>

int is_pandigital(long a, long b, long c)
{
    int appeared[10] = {0};

    while (a > 0) {
        appeared[a % 10L]++;
        a /= 10L;
    }

    while (b > 0) {
        appeared[b % 10L]++;
        b /= 10L;
    }

    while (c > 0) {
        appeared[c % 10L]++;
        c /= 10L;
    }

    if (appeared[0]) {
        return 0;
    }

    for (int i = 1; i < 10; i++) {
        if (appeared[i] != 1) {
            return 0;
        }
    }

    return 1;
}

void insertion_sort(long *a, int n)
{
    for (int i = 1; i < n; i++) {
        if (a[i] < a[i - 1]) {
            long tmp = a[i];
            int j = i;
            do {
                a[j] = a[j - 1];
                j--;
            } while (j > 0 && tmp < a[j - 1]);
            a[j] = tmp;
        }
    }
}

int main(void)
{
    long results[16];
    int count = 0;

    // The possible combinations are:
    // - 1-digit * 4-digit = 4-digit
    // - 2-digit * 3-digit = 4-digit

    // 1-digit * 4-digit = 4-digit
    for (long a = 1L; a < 10L; a++) {
        for (long b = 1000L; b < 10000L; b++) {
            long c = a * b;
            if (is_pandigital(a, b, c)) {
                results[count++] = c;
            }
        }
    }

    // 2-digit * 3-digit = 4-digit
    for (long a = 10L; a < 100L; a++) {
        for (long b = 100L; b < 1000L; b++) {
            long c = a * b;
            if (is_pandigital(a, b, c)) {
                results[count++] = c;
            }
        }
    }

    insertion_sort(results, count);

    long cur = results[0];
    long total = cur;
    for (int i = 1; i < count; i++) {
        if (results[i] == cur) {
            continue;
        }
        total += (cur = results[i]);
    }

    printf("%ld\n", total);

    return 0;
}
