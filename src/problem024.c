// Lexicographic Permutations
// 2783915460

#define TARGET 1000000L // 1 million
#define NUM 10
#define LEN 64

#include <stdio.h>

// Fill `dst` with a permutation of 0, 1, ..., `perm_len` - 1 whose order is specified by `order`
// ex. fill_permutation(dst, 3, 0) -> dst = {0, 1, 2}
// ex. fill_permutation(dst, 3, 5) -> dst = {2, 1, 0}
// ex. fill_permutation(dst, 3, 6) -> dst = {0, 1, 2}
// `order` should be >= 0
// If `order` >= `perm_len`!, `order` % `perm_len`! is used as `order`
void fill_permutation(int *dst, int perm_len, long order)
{
    int terms[LEN];

    for (int i = 1; i <= perm_len; i++) {
        terms[i - 1] = order % i;
        order /= i;
    }

    int used[LEN] = {0};
    int idx = 0;

    for (int i = perm_len - 1; i >= 0; i--) {
        int term = terms[i];

        for (int j = 0; j < perm_len; j++) {
            if (!used[j] && term-- == 0) {
                dst[idx++] = j;
                used[j] = 1;
                break;
            }
        }
    }
}

void println_arr(const int *arr, int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
    }
    putchar('\n');
}

int main(void)
{
    int perm[NUM];

    fill_permutation(perm, NUM, TARGET - 1);

    println_arr(perm, NUM);

    return 0;
}
