// Cyclical Figurate Numbers
// 8256(tri) + 5625(hep) + 2512(hex) + 1281(squ) + 8128(oct) + 2882(pen) = 28684

#include <stdio.h>

#define N 6
#define LEN 100
#define BEGIN 1000
#define END 10000

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

int bin_search(const int *array, int array_size, int target)
{
    int l = 0;
    int r = array_size;
    int m;

    do {
        m = (l + r) / 2;
        if (array[m] >= target) {
            r = m;
        } else {
            l = m + 1;
        }
    } while (l < r);

    if (l < array_size && array[l] == target) {
        return l;
    }
    return -l - 1;
}

int triangle_number(int n)
{
    return n * (n + 1) / 2;
}

int square_number(int n)
{
    return n * n;
}

int pentagonal_number(int n)
{
    return n * (3 * n - 1) / 2;
}

int hexagonal_number(int n)
{
    return n * (2 * n - 1);
}

int heptagonal_number(int n)
{
    return n * (5 * n - 3) / 2;
}

int octagonal_number(int n)
{
    return n * (3 * n - 2);
}

int fill_numbers(int *dst, int begin, int end, int (*fn)(int))
{
    int n;
    int number;

    for (n = 1; ; n++) {
        number = fn(n);
        if (number >= begin) {
            break;
        }
    }

    int count = 0;

    for (n++; number < end; n++) {
        if (number % 100 >= 10) {
            dst[count++] = number;
        }
        number = fn(n);
    }

    return count;
}

int glue(int a, int b)
{
    return a % 100 * 100 + b / 100;
}

int main(void)
{
    int numbers[N][LEN];
    int len[N];

    len[0] = fill_numbers(numbers[0], BEGIN, END, triangle_number);
    len[1] = fill_numbers(numbers[1], BEGIN, END, square_number);
    len[2] = fill_numbers(numbers[2], BEGIN, END, pentagonal_number);
    len[3] = fill_numbers(numbers[3], BEGIN, END, hexagonal_number);
    len[4] = fill_numbers(numbers[4], BEGIN, END, heptagonal_number);
    len[5] = fill_numbers(numbers[5], BEGIN, END, octagonal_number);

    int nums[N / 2];
    int glues[N / 2];
    int perm[N / 2];

    int res = 0;

    for (int i = 1; i < N; i++) {
        for (int j = 1; j < N; j++) {
            if (i == j) {
                continue;
            }

            for (int k = 1, idx = 0; k < N; k++) {
                if (k != i && k != j) {
                    perm[idx++] = k;
                }
            }

            int l1 = len[0], l2 = len[i], l3 = len[j];

            for (int i1 = 0; i1 < l1; i1++) {
                nums[0] = numbers[0][i1];
                for (int i2 = 0; i2 < l2; i2++) {
                    nums[1] = numbers[i][i2];
                    for (int i3 = 0; i3 < len[j]; i3++) {
                        nums[2] = numbers[j][i3];
                        glues[0] = glue(nums[0], nums[1]);
                        glues[1] = glue(nums[1], nums[2]);
                        glues[2] = glue(nums[2], nums[0]);

                        do {
                            if (
                                bin_search(numbers[perm[0]], len[perm[0]], glues[0]) >= 0
                                && bin_search(numbers[perm[1]], len[perm[1]], glues[1]) >= 0
                                && bin_search(numbers[perm[2]], len[perm[2]], glues[2]) >= 0
                            ) {
                                for (int k = 0; k < N / 2; k++) {
                                    res += nums[k] + glues[k];
                                }
                                // printf("%d %d %d %d %d %d\n", nums[0], glues[0], nums[1], glues[1], nums[2], glues[2]);
                                // printf("0->%d->%d->%d->%d->%d\n", i, j, perm[0], perm[1], perm[2]);
                                goto Finally;
                            }
                        } while (next_permutation(perm, N / 2));
                    }
                }
            }
        }
    }

Finally:
    printf("%d\n", res);

    return 0;
}
