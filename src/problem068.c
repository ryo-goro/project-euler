// Magic 5-gon Ring

#include <stdio.h>

#define N 5

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

int main(void)
{
    // 10 must be one of the outer nodes as the result should be a 16-digit number
    // We can assume outer[0] = 10 due to the symmetry
    int outer[N] = {10};
    int inner[N];

    int one_digit_nodes[2 * N - 1];
    for (int i = 0; i < 2 * N - 1; i++) {
        one_digit_nodes[i] = i + 1;
    }

    unsigned long long res = 0;

    do {
        for (int i = 0; i < N - 1; i++) {
            outer[i + 1] = one_digit_nodes[i];
        }
        for (int i = 0; i < N; i++) {
            inner[i] = one_digit_nodes[i + N - 1];
        }

        int magical = 1;

        for (int i = 0; i < N - 2; i++) {
            if (outer[i] + inner[i] != outer[i + 1] + inner[i + 2]) {
                magical = 0;
                break;
            }
        }

        if (!magical || outer[N - 2] + inner[N - 2] != outer[N - 1] + inner[0]) {
            continue;
        }

        // Determines which node to start the concatenation from
        int idx = 1;
        for (int i = 2; i < N; i++) {
            if (outer[i] < outer[idx]) {
                idx = i;
            }
        }

        unsigned long long candidate = 0;

        for (int i = 0; i < N; i++) {
            if (outer[idx] == 10) {
                candidate *= 100;
            } else {
                candidate *= 10;
            }
            candidate += outer[idx];

            candidate *= 10;
            candidate += inner[idx];

            if (++idx == N) {
                idx = 0;
            }

            candidate *= 10;
            candidate += inner[idx];
        }

        if (candidate > res) {
            res = candidate;
        }
    } while (next_permutation(one_digit_nodes, 2 * N - 1));

    printf("%llu\n", res);

    return 0;
}
