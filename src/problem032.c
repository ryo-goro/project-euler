// Pandigital Products
// 45228

#include <stdio.h>

int num_of_digits(long target)
{
    int len = 1;
    long pow10 = 10;

    while (target >= pow10) {
        len++;
        pow10 *= 10;
    }

    return len;
}

int is_pandigital(int a, int b, int c)
{
    int counts[10] = {0};

    while (a > 0) {
        counts[a % 10]++;
        a /= 10;
    }

    while (b > 0) {
        counts[b % 10]++;
        b /= 10;
    }

    while (c > 0) {
        counts[c % 10]++;
        c /= 10;
    }

    if (counts[0] > 0) {
        return 0;
    }

    for (int i = 1; i < 10; i++) {
        if (counts[i] != 1) {
            return 0;
        }
    }

    return 1;
}

void insertion_sort(int *arr, int n)
{
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i - 1]) {
            int tmp = arr[i];
            int j = i;

            do {
                arr[j] = arr[j - 1];
                j--;
            } while (j > 0 && tmp < arr[j - 1]);

            arr[j] = tmp;
        }
    }
}

int compress_sorted_arr(int *sorted_arr, int n)
{
    if (n <= 0) {
        return 0;
    }

    int target = sorted_arr[0];
    int len = 1;

    for (int i = 1; i < n; i++) {
        if (target != sorted_arr[i]) {
            sorted_arr[len++] = target = sorted_arr[i];
        }
    }

    return len;
}

int sumof(const int *arr, int n)
{
    int res = 0;
    
    for (int i = 0; i < n; i++) {
        res += arr[i];
    }

    return res;
}

int main(void)
{
    int results[16];
    int count = 0;

    // The possible combinations are:
    // - 1-digit * 4-digit = 4-digit
    // - 2-digit * 3-digit = 4-digit

    // 1-digit * 4-digit = 4-digit
    for (int a = 1; a < 10; a++) {
        for (int b = 1000; b < 10000; b++) {
            long c = ((long)a) * b;

            if (num_of_digits(c) > 4) {
                break;
            }

            if (is_pandigital(a, b, (int)c)) {
                results[count++] = c;
            }
        }
    }

    // 2-digit * 3-digit = 4-digit
    for (int a = 10; a < 100; a++) {
        for (int b = 100; b < 1000; b++) {
            long c = ((long)a) * b;

            if (num_of_digits(c) > 4) {
                break;
            }

            if (is_pandigital(a, b, (int)c)) {
                results[count++] = c;
            }
        }
    }

    insertion_sort(results, count);
    int unique_count = compress_sorted_arr(results, count);

    printf("%d\n", sumof(results, unique_count));

    return 0;
}
