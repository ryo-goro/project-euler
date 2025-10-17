// Pandigital Prime
// 7652413

#include <stdio.h>

#define swap(type, x, y)    do { type t = x; x = y; y = t; } while (0)

void reverse_arr(int *arr, int begin, int end)
{
    for (int i = 0, h = (end - begin) / 2; i < h; i++) {
        int tmp = arr[begin + i];
        arr[begin + i] = arr[end - 1 - i];
        arr[end - 1 - i] = tmp;
    }
}

int next_permutation_desc(int *perm, int perm_len)
{
    int i = perm_len - 2;
    for (; i >= 0; i--) {
        if (perm[i] > perm[i + 1]) {
            break;
        }
    }

    if (i < 0) {
        reverse_arr(perm, 0, perm_len);
        return 0;
    }

    int tmp = perm[i];
    int j = perm_len - 1;
    for (; j > i; j--) {
        if (perm[j] < tmp) {
            break;
        }
    }

    swap(int, perm[i], perm[j]);
    reverse_arr(perm, i + 1, perm_len);

    return 1;
}

// Example: to_long({9, 6, 7, 8}, 3) = 967
long to_long(const int *digits, int n)
{
    long res = 0;

    for (int i = 0; i < n; i++) {
        res = res * 10 + digits[i];
    }

    return res;
}

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

int main(void)
{
    // By checking whether the sum of each digit is divisible by 3,
    // we see that only 4 or 7-digit pandigital numbers can be prime

    // Scan 7-digit pandigital numbers in descending order
    int digits7[] = {7, 6, 5, 4, 3, 2, 1};
    do {
        long candidate = to_long(digits7, 7);
        if (is_prime(candidate)) {
            printf("%ld\n", candidate);

            return 0;
        }
    } while (next_permutation_desc(digits7, 7));

    // Scan 4-digit pandigital numbers in descending order
    int digits4[] = {4, 3, 2, 1};
    do {
        long candidate = to_long(digits4, 4);
        if (is_prime(candidate)) {
            printf("%ld\n", candidate);
            break;
        }
    } while (next_permutation_desc(digits4, 4));

    return 0;
}
