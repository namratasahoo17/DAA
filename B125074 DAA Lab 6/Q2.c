#include <stdio.h>
#include <stdlib.h>

/*
===========================================================
QUESTION 2: 0/1 KNAPSACK USING DYNAMIC PROGRAMMING
===========================================================

Implement the 0/1 Knapsack problem using Dynamic
Programming.

Given n items with their weights and profits and a
knapsack of capacity W, determine the maximum profit
that can be obtained.

Analyze the time and space complexity of the algorithm.


-----------------------------------------------------------
PSEUDOCODE
-----------------------------------------------------------

KNAPSACK(n, W, weight, profit)

    Create DP table dp[n+1][W+1]

    for i = 0 to n

        for w = 0 to W

            if i == 0 OR w == 0

                dp[i][w] = 0

            else if weight[i-1] <= w

                include =
                    profit[i-1] +
                    dp[i-1][w-weight[i-1]]

                exclude =
                    dp[i-1][w]

                dp[i][w] = maximum(include, exclude)

            else

                dp[i][w] = dp[i-1][w]

    return dp[n][W]


-----------------------------------------------------------
MEANING OF 0/1
-----------------------------------------------------------

For every item, there are only two choices:

    0 -> Do not take the item

    1 -> Take the item

An item cannot be taken more than once.


-----------------------------------------------------------
COMPLEXITY ANALYSIS
-----------------------------------------------------------

Time Complexity  : O(N * W)

Space Complexity : O(N * W)

where:

    N = number of items
    W = knapsack capacity

The DP table contains (N+1) x (W+1) states.


===========================================================
*/

int maximum(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

int knapsack(int n, int capacity, int weight[], int profit[])
{
    /*
        Allocate a 2D DP table.

        dp[i][w] represents the maximum profit that can
        be obtained using the first i items with capacity w.
    */

    int **dp = (int **)malloc((n + 1) * sizeof(int *));

    if (dp == NULL)
    {
        printf("Memory allocation failed.\n");
        return -1;
    }

    for (int i = 0; i <= n; i++)
    {
        dp[i] = (int *)malloc((capacity + 1) * sizeof(int));

        if (dp[i] == NULL)
        {
            printf("Memory allocation failed.\n");
            return -1;
        }
    }

    /*
        Build the DP table.
    */

    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= capacity; w++)
        {
            /*
                No items or zero capacity gives zero profit.
            */
            if (i == 0 || w == 0)
            {
                dp[i][w] = 0;
            }

            /*
                Current item can fit in the knapsack.
            */
            else if (weight[i - 1] <= w)
            {
                /*
                    Option 1: Include the item.
                */
                int include =
                    profit[i - 1] +
                    dp[i - 1][w - weight[i - 1]];

                /*
                    Option 2: Exclude the item.
                */
                int exclude =
                    dp[i - 1][w];

                /*
                    Choose the better option.
                */
                dp[i][w] = maximum(include, exclude);
            }

            /*
                Current item cannot fit.
            */
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    int result = dp[n][capacity];

    /*
        Free the DP table.
    */
    for (int i = 0; i <= n; i++)
    {
        free(dp[i]);
    }

    free(dp);

    return result;
}

int main()
{
    int n;
    int capacity;

    printf("Enter number of items: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Number of items must be positive.\n");
        return 1;
    }

    printf("Enter knapsack capacity: ");
    scanf("%d", &capacity);

    int *weight = (int *)malloc(n * sizeof(int));
    int *profit = (int *)malloc(n * sizeof(int));

    if (weight == NULL || profit == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("\nEnter weights of the items:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &weight[i]);
    }

    printf("\nEnter profits of the items:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &profit[i]);
    }

    int result = knapsack(n, capacity, weight, profit);

    printf("\nMaximum Profit = %d\n", result);

    free(weight);
    free(profit);

    return 0;
}