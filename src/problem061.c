// Cyclical Figurate Numbers
// 28684
// 8256(3) + 5625(4) + 2512(7) + 1281(8) + 8128(6) + 2882(5)

#include <stdio.h>
#include <stdlib.h>

#define NUM_OF_POLYGONAL_TYPES 6
#define NUM_OF_DIGITS 4
#define SUFFIX_LEN 2
#define INITIAL_ARRAYLIST_CAPACITY 256

#define swap(type, x, y)    do { type t = x; x = y; y = t; } while (0)

typedef struct {
    long *array;
    int size;
    int capacity;
} LongArrayList;

int LAL_initialize(LongArrayList *list, int initial_capacity)
{
    list->size = 0;

    if (initial_capacity > 0) {
        if ((list->array = (long *)calloc(initial_capacity, sizeof(long))) == NULL) {
            // Out of memory
            list->capacity = 0;
            return 1;
        }
        list->capacity = initial_capacity;
    } else {
        list->array = NULL;
        list->capacity = 0;
    }

    return 0;
}

int LAL_add(LongArrayList *list, long value)
{
    if (list->size >= list->capacity) {
        long *tmp_arr = (long *)realloc(list->array, list->capacity * 2 * sizeof(long));
        if (tmp_arr == NULL) {
            // Out of memory
            return 1;
        }
        list->array = tmp_arr;
        list->capacity *= 2;
    }

    list->array[list->size++] = value;
    return 0;
}

// `idx` should be `0 <= idx < list->size`
long LAL_get(const LongArrayList *list, int idx)
{
    return list->array[idx];
}

int LAL_size(const LongArrayList *list)
{
    return list->size;
}

void LAL_free(LongArrayList *list)
{
    free(list->array);
    list->array = NULL;
    list->size = list->capacity = 0;
}

int LAL_lower_bound(const LongArrayList *list, long target)
{
    int l = 0;
    int r = list->size;

    while (l < r) {
        int m = (l + r) / 2;

        if (list->array[m] >= target) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    return l;
}

// Returns a^n
long power(long a, int n)
{
    long res = 1;

    for (int i = 0; i < n; i++) {
        res *= a;
    }

    return res;
}

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

long polygonal_number(int type, long n)
{
    return n * ((type - 2) * n - type + 4) / 2;
}

long prefix(long num, int prefix_len)
{
    long pow10 = 10;
    int digits_count = 1;

    while (pow10 <= num) {
        pow10 *= 10;
        digits_count++;
    }

    if (prefix_len > digits_count) {
        return num;
    }

    return num / power(10, digits_count - prefix_len);
}

long suffix(long num, int suffix_len)
{
    return num % power(10, suffix_len);
}

int main(void)
{
    LongArrayList polygonal_numbers[NUM_OF_POLYGONAL_TYPES];
    for (int i = 0; i < NUM_OF_POLYGONAL_TYPES; i++) {
        LAL_initialize(&polygonal_numbers[i], INITIAL_ARRAYLIST_CAPACITY);
    }

    for (int i = 0; i < NUM_OF_POLYGONAL_TYPES; i++) {
        const long begin = power(10, NUM_OF_DIGITS - 1);
        const long end = begin * 10;

        const int polygonal_type = i + 3;
        int n = 1;

        for (;; n++) {
            if (polygonal_number(polygonal_type, n) >= begin) {
                break;
            }
        }

        for (;; n++) {
            const long num = polygonal_number(polygonal_type, n);
            if (num >= end) {
                break;
            }

            LAL_add(&polygonal_numbers[i], num);
        }
    }

    // Backtracking method

    int perm[NUM_OF_POLYGONAL_TYPES];
    for (int i = 0; i < NUM_OF_POLYGONAL_TYPES; i++) {
        perm[i] = i;
    }

    do {
        int begin_stk[NUM_OF_POLYGONAL_TYPES];
        int end_stk[NUM_OF_POLYGONAL_TYPES];
        int idx_stk[NUM_OF_POLYGONAL_TYPES];

        begin_stk[0] = idx_stk[0] = 0;
        end_stk[0] = LAL_size(&polygonal_numbers[perm[0]]);

        int stk_size = 1;

        while (stk_size > 0) {
            const int idx = idx_stk[stk_size - 1];

            if (idx >= end_stk[stk_size - 1]) {
                stk_size--;
                if (stk_size > 0) {
                    idx_stk[stk_size - 1]++;
                }

                continue;
            }

            const long suf = suffix(LAL_get(&polygonal_numbers[perm[stk_size - 1]], idx), SUFFIX_LEN);
            const long lower_bound = suf * power(10, NUM_OF_DIGITS - SUFFIX_LEN);
            const long upper_bound = (suf + 1) * power(10, NUM_OF_DIGITS - SUFFIX_LEN);

            const LongArrayList *next_list = &polygonal_numbers[perm[stk_size]];

            const int next_begin = LAL_lower_bound(next_list, lower_bound);
            const int next_end = LAL_lower_bound(next_list, upper_bound);

            if (next_begin >= next_end) {
                idx_stk[stk_size - 1]++;
                continue;
            }

            begin_stk[stk_size] = idx_stk[stk_size] = next_begin;
            end_stk[stk_size] = next_end;
            stk_size++;

            if (stk_size == NUM_OF_POLYGONAL_TYPES) {
                const long first_prefix = prefix(LAL_get(&polygonal_numbers[perm[0]], idx_stk[0]), SUFFIX_LEN);

                for (int last_idx = next_begin; last_idx < next_end; last_idx++) {
                    const long last_suffix = suffix(LAL_get(next_list, last_idx), SUFFIX_LEN);

                    if (last_suffix == first_prefix) {
                        long res = 0;
                        for (int i = 0; i < NUM_OF_POLYGONAL_TYPES; i++) {
                            res += LAL_get(&polygonal_numbers[perm[i]], idx_stk[i]);
                        }
                        printf("%ld\n", res);

                        goto Finally;
                    }
                }

                stk_size--;
                idx_stk[stk_size - 1]++;
            }
        }
    } while (next_permutation(perm, NUM_OF_POLYGONAL_TYPES));

Finally:
    // Free memory
    for (int i = 0; i < NUM_OF_POLYGONAL_TYPES; i++) {
        LAL_free(&polygonal_numbers[i]);
    }

    return 0;
}
