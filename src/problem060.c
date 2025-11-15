// Prime Pair Sets
// 26033
// 13 + 5197 + 5701 + 6733 + 8389

#include <stdio.h>
#include <stdlib.h>

#define SIEVE_SIZE 1000000L
#define INITIAL_PRIMES_CAPACITY 1024
#define INITIAL_ARRAY_CAPACITY 16
#define PRIME_LIMIT 10000
#define STACK_CAPACITY 5

typedef struct {
    int *array;
    int size;
    int capacity;
} IntArrayList;

int IAL_initialize(IntArrayList *list, int initial_capacity)
{
    list->size = 0;

    if (initial_capacity > 0) {
        if ((list->array = (int *)calloc(initial_capacity, sizeof(int))) == NULL) {
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

int IAL_add(IntArrayList *list, int value)
{
    if (list->size >= list->capacity) {
        int *tmp_arr = (int *)realloc(list->array, list->capacity * 2 * sizeof(int));
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
int IAL_get(const IntArrayList *list, int idx)
{
    return list->array[idx];
}

int IAL_size(const IntArrayList *list)
{
    return list->size;
}

void IAL_free(IntArrayList *list)
{
    free(list->array);
    list->array = NULL;
    list->size = list->capacity = 0;
}

int IAL_bsearch(const IntArrayList *list, int target)
{
    int l = 0;
    int r = list->size;

    do {
        int m = (l + r) / 2;

        if (list->array[m] >= target) {
            r = m;
        } else {
            l = m + 1;
        }
    } while (l < r);

    if (l < list->size && list->array[l] == target) {
        // target found
        return l;
    }

    // target not found
    return -l - 1;
}

void make_sieve(char *sieve, long sieve_len)
{
    if (sieve_len <= 0L) {
        return;
    }

    sieve[0] = 0;

    if (sieve_len == 1L) {
        return;
    }

    sieve[1] = 0;

    for (long i = 2L; i < sieve_len; i++) {
        sieve[i] = 1;
    }
    
    for (long i = 4L; i < sieve_len; i += 2L) {
        sieve[i] = 0;
    }

    for (long i = 3L; i * i < sieve_len; i += 2L) {
        if (sieve[i]) {
            for (long j = i * i; j < sieve_len; j += i) {
                sieve[j] = 0;
            }
        }
    }
}

int is_prime(long long target)
{
    if (target < 2LL) {
        return 0;
    }

    if (target == 2LL) {
        return 1;
    }

    if (target % 2 == 0LL) {
        return 0;
    }

    for (long long d = 3; d * d <= target; d += 2) {
        if (target % d == 0LL) {
            return 0;
        }
    }

    return 1;
}

// `target` should be >= 0
int is_prime_with_sieve(long long target, const char *sieve, long sieve_len)
{
    if (target < sieve_len) {
        return sieve[target];
    }

    return is_prime(target);
}

// Example: concat(12, 345) = 12345
// Example: concat(1000, 0) = 10000
long long concat(long a, long b)
{
    long pow10 = 10;

    while (pow10 <= b) {
        pow10 *= 10;
    }

    return (long long)a * pow10 + b;
}

int main(void)
{
    char prime_sieve[SIEVE_SIZE];   // The sieve of Eratosthenes
    make_sieve(prime_sieve, SIEVE_SIZE);

    IntArrayList primes;

    IAL_initialize(&primes, INITIAL_PRIMES_CAPACITY);
    IAL_add(&primes, 3);

    // 6k + 1
    // No candidate was found for 6k + 5
    for (int p = 7; p < PRIME_LIMIT; p += 6) {
        if (prime_sieve[p]) {
            IAL_add(&primes, p);
        }
    }

    const int num_of_primes = IAL_size(&primes);

    // `concat_idxs[i]` is an IntArrayList whose `array` consists of the indexes of `primes.array` which are > `i` in ascending order
    // And for any element `j` of `concat_idxs[i].array`,
    // `primes.array[j]` forms prime numbers by concatenating with `primes.array[i]`
    IntArrayList *concat_idxs = (IntArrayList *)calloc(num_of_primes - 1, sizeof(IntArrayList));

    for (int i = 0; i < num_of_primes - 1; i++) {
        IntArrayList *idxs = &concat_idxs[i];
        IAL_initialize(idxs, INITIAL_ARRAY_CAPACITY);

        int prime_i = IAL_get(&primes, i);

        for (int j = i + 1; j < num_of_primes; j++) {
            int prime_j = IAL_get(&primes, j);

            if (is_prime_with_sieve(concat(prime_i, prime_j), prime_sieve, SIEVE_SIZE)
                && is_prime_with_sieve(concat(prime_j, prime_i), prime_sieve, SIEVE_SIZE)
            ) {
                IAL_add(idxs, j);
            }
        }
    }

    for (int i = 0; i < num_of_primes - 1; i++) {
        // Check if a set whose minimun value is `primes.array[i]` is an answer

        int idx_stk[STACK_CAPACITY];
        int itr_stk[STACK_CAPACITY];

        idx_stk[0] = i;
        itr_stk[0] = 0;

        int stk_size = 1;

        while (stk_size > 0) {
            const int idx = idx_stk[stk_size - 1];
            const IntArrayList *next_idxs = &concat_idxs[idx];
            const int itr_limit = IAL_size(next_idxs);
            int itr = itr_stk[stk_size - 1];

            for (; itr < itr_limit; itr++) {
                const int next_idx = IAL_get(next_idxs, itr);
                char next_ok = 1;
                for (int j = stk_size - 2; j >= 0; j--) {
                    if (IAL_bsearch(&concat_idxs[idx_stk[j]], next_idx) < 0) {
                        next_ok = 0;
                        break;
                    }
                }

                // Found a new candidate
                if (next_ok) {
                    idx_stk[stk_size] = next_idx;
                    itr_stk[stk_size - 1] = itr + 1;
                    itr_stk[stk_size] = 0;
                    stk_size++;

                    if (stk_size == STACK_CAPACITY) {
                        printf("Found:");
                        for (int j = 0; j < stk_size; j++) {
                            printf(" %d", IAL_get(&primes, idx_stk[j]));
                        }
                        putchar('\n');
                        stk_size--;
                    }

                    break;
                }
            }

            if (itr == itr_limit) {
                stk_size--;
            }
        }
    }

    // Free memory
    IAL_free(&primes);
    for (int i = 0; i < num_of_primes - 1; i++) {
        IAL_free(&concat_idxs[i]);
    }
    free(concat_idxs);

    return 0;
}
