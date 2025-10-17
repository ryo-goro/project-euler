// Sub-string Divisibility
// 16695334890

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

int next_permutation(int *perm, int perm_len)
{
    int i = perm_len - 2;
    for (; i >= 0; i--) {
        if (perm[i] < perm[i + 1]) {
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
        if (perm[j] > tmp) {
            break;
        }
    }

    swap(int, perm[i], perm[j]);
    reverse_arr(perm, i + 1, perm_len);

    return 1;
}

// Example: to_ll({9, 6, 7, 8}, 3) = 967
long long to_ll(const int *digits, int n)
{
    long long res = 0;

    for (int i = 0; i < n; i++) {
        res = res * 10 + digits[i];
    }

    return res;
}

// Example: to_int({9, 6, 7, 8, 9}, 1, 3) = 67
int to_int(const int *digits, int begin, int end)
{
    int res = 0;

    for (int i = begin; i < end; i++) {
        res = res * 10 + digits[i];
    }

    return res;
}

int main(void)
{
    int primes[] = {2, 3, 5, 7, 11, 13, 17};
    int num_of_primes = sizeof(primes) / sizeof(primes[0]);

    int digits[] = {1, 0, 2, 3, 4, 5, 6, 7, 8, 9};  // Skip numbers with a leading 0
    int num_of_digits = sizeof(digits) / sizeof(digits[0]);

    long long res = 0;

    do {
        int i = 0;

        for (; i < num_of_primes; i++) {
            if (to_int(digits, i + 1, i + 4) % primes[i] != 0) {
                break;
            }
        }

        if (i == num_of_primes) {
            res += to_ll(digits, num_of_digits);
        }
    } while (next_permutation(digits, num_of_digits));

    printf("%lld\n", res);

    return 0;
}
