#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int minCoins(int coins[], int n, int amount)
{
    int *dp = malloc((amount + 1) * sizeof(int));

    // dp[0] = 0 because zero coins are needed to make amount 0
    dp[0] = 0;

    // Initialize all other values to a large number
    for (int i = 1; i <= amount; i++)
        dp[i] = INT_MAX;

    // Calculate the answer for every amount from 1 to amount
    for (int i = 1; i <= amount; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (coins[j] <= i && dp[i - coins[j]] != INT_MAX)
            {
                dp[i] = (dp[i] < dp[i - coins[j]] + 1)
                        ? dp[i]
                        : dp[i - coins[j]] + 1;
            }
        }
    }

    int answer = (dp[amount] == INT_MAX) ? -1 : dp[amount];

    free(dp);

    return answer;
}

int main()
{
    int n, amount;

    printf("Enter number of coin denominations: ");
    scanf("%d", &n);

    int *coins = malloc(n * sizeof(int));

    printf("Enter coin denominations: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &coins[i]);

    printf("Enter target amount: ");
    scanf("%d", &amount);

    int result = minCoins(coins, n, amount);

    printf("Minimum number of coins = %d\n", result);

    free(coins);

    return 0;
}