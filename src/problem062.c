// Cubic Permutations
// 5027^3 = 127035954683, 7061^3 = 352045367981, 7202^3 = 373559126408, 8288^3 = 569310543872, 8384^3 = 589323567104

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 1024
#define N 5

typedef struct entry {
    unsigned char digits_count[10];
    unsigned count;
    unsigned n;
    struct entry *next;
} Entry;

unsigned hash(unsigned char *digits_count, unsigned mod)
{
    unsigned h = 0;

    for (int i = 0; i < 10; i++) {
        h = h * 31 + digits_count[i];
    }

    return h % mod;
}

void count_digits(unsigned char *digits_count, unsigned long long target)
{
    for (int i = 0; i < 10; i++) {
        digits_count[i] = 0;
    }

    while (target) {
        digits_count[target % 10]++;
        target /= 10;
    }
}

void array_copy(unsigned char *dst, const unsigned char *src, int n)
{
    for (int i = 0; i < n; i++) {
        dst[i] = src[i];
    }
}

int array_eq(const unsigned char *a, const unsigned char *b, int n)
{
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}

unsigned long long cube(unsigned long long n)
{
    return n * n * n;
}

int main(void)
{
    Entry *table[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = NULL;
    }

    unsigned long long power10 = 10;
    unsigned char digits_count[10];
    unsigned res = UINT_MAX;

    for (unsigned n = 1; ; n++) {
        unsigned long long n3 = cube(n);

        if (n3 < power10) {
            count_digits(digits_count, n3);

            unsigned idx = hash(digits_count, TABLE_SIZE);
            Entry *entry = table[idx];

            while (entry != NULL) {
                if (array_eq(entry->digits_count, digits_count, 10)) {
                    entry->count++;
                    break;
                }
                entry = entry->next;
            }

            if (entry == NULL) {
                entry = (Entry *)malloc(sizeof(Entry));
                array_copy(entry->digits_count, digits_count, 10);
                entry->count = 1;
                entry->n = n;
                entry->next = table[idx];
                table[idx] = entry;
            }
        } else {
            for (int i = 0; i < TABLE_SIZE; i++) {
                Entry *entry = table[i];
                while (entry != NULL) {
                    if (entry->count == N && entry->n < res) {
                        res = entry->n;
                    }
                    entry = entry->next;
                }
            }

            for (int i = 0; i < TABLE_SIZE; i++) {
                Entry *entry = table[i];
                while (entry != NULL) {
                    Entry *tmp = entry->next;
                    free(entry);
                    entry = tmp;
                }
            }

            if (res < UINT_MAX) {
                break;
            }

            for (int i = 0; i < TABLE_SIZE; i++) {
                table[i] = NULL;
            }
            power10 *= 10;
            n--;
        }
    }

    printf("%llu\n", cube(res));

    return 0;
}
