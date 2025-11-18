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
#define INFINITY 1000000L

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
int is_prime_with_sieve(long long target)
{
    static char sieve[SIEVE_SIZE];
    static char sieve_is_initialized = 0;

    if (!sieve_is_initialized) {
        make_sieve(sieve, SIEVE_SIZE);
        sieve_is_initialized = 1;
    }

    if (target < SIEVE_SIZE) {
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
    // `primes` is an IntArrayList whose `array` consists of prime numbers that are < PRIME_LIMIT
    // For the array to contain the prime numbers that solves the problem, the following must hold true:
    // - The array does not contain 2 and 5 because every prime number the number of digits of which is > 1
    //   does not end with 2 or 5.
    // - The array does not simultaneously contain prime numbers
    //   whose remainder when divided by 3 is 1 and prime numbers whose remainder is 2
    //   because a number obtained by concatenating those numbers is divisible by 3.
    IntArrayList primes;
    IAL_initialize(&primes, INITIAL_PRIMES_CAPACITY);

    IAL_add(&primes, 3);

    // 6k + 1
    // No candidate was found for 6k + 5
    for (int p = 7; p < PRIME_LIMIT; p += 6) {
        if (is_prime_with_sieve(p)) {
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

        int p_i = IAL_get(&primes, i);

        for (int j = i + 1; j < num_of_primes; j++) {
            int p_j = IAL_get(&primes, j);

            if (is_prime_with_sieve(concat(p_i, p_j)) && is_prime_with_sieve(concat(p_j, p_i))) {
                IAL_add(idxs, j);
            }
        }
    }

    long res = INFINITY;

    for (int i = 0; i < num_of_primes - 1; i++) {
        // Check if a set whose minimum value is `primes.array[i]` is an answer

        // For any `x` and `y` such that `0 <= x < y < stk_size`,
        // the concatenations of `primes.array[idx_stk[x]]` and `primes.array[idx_stk[y]]` are prime
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

                if (next_ok) {
                    idx_stk[stk_size] = next_idx;
                    itr_stk[stk_size - 1] = itr + 1;
                    itr_stk[stk_size] = 0;
                    stk_size++;

                    if (stk_size == STACK_CAPACITY) {
                        long sum = 0;
                        for (int j = 0; j < STACK_CAPACITY; j++) {
                            sum += IAL_get(&primes, idx_stk[j]);
                        }
                        if (sum < res) {
                            res = sum;
                        }

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

    if (res < INFINITY) {
        printf("%ld\n", res);
    } else {
        puts("Answer not found");
    }

    // Free memory
    IAL_free(&primes);
    for (int i = 0; i < num_of_primes - 1; i++) {
        IAL_free(&concat_idxs[i]);
    }
    free(concat_idxs);

    return 0;
}
