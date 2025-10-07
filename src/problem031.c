// Coin Sums
// 73682

#include <stdio.h>

#define NUM_OF_COINS 8
#define TARGET_AMOUNT 200

int main(void)
{
    int coins[NUM_OF_COINS] = {
        1, 2, 5, 10, 20, 50, 100, 200,
    };

    long dp[TARGET_AMOUNT + 1] = {1};

    for (int i = 0; i < NUM_OF_COINS; i++) {
        int coin = coins[i];

        for (int amount = coin; amount <= TARGET_AMOUNT; amount++) {
            dp[amount] += dp[amount - coin];
        }

        // Here, dp[amount] means "how many different ways `amount` can be made using coins[0], coins[1], ..., coins[i]"
    }

    printf("%ld\n", dp[TARGET_AMOUNT]);

    return 0;
}
