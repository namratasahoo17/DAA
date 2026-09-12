#include <stdio.h>
#include <stdlib.h>

/*
===========================================================
QUESTION 2: SUPER EGG TESTING EXPERIMENT
===========================================================

A firm has two identical eggs and a 100-storey building.
The objective is to determine the highest floor from which
an egg can fall without breaking.

The same egg can be dropped multiple times unless it breaks.

Find the minimum number of droppings guaranteed to determine
the highest safe floor.

Also generalize the solution for E eggs and F floors using
Dynamic Programming.


-----------------------------------------------------------
PSEUDOCODE
-----------------------------------------------------------

EGG_DROP(E, F)

    Create array dp[E + 1][F + 1]

    for e = 1 to E
        dp[e][0] = 0
        dp[e][1] = 1

    for f = 1 to F
        dp[1][f] = f

    for e = 2 to E

        for f = 2 to F

            dp[e][f] = infinity

            for x = 1 to f

                broken = dp[e - 1][x - 1]

                notBroken = dp[e][f - x]

                attempts = 1 + max(broken, notBroken)

                if attempts < dp[e][f]
                    dp[e][f] = attempts

    return dp[E][F]


MAIN

    Read E
    Read F

    result = EGG_DROP(E, F)

    Display result


-----------------------------------------------------------
DYNAMIC PROGRAMMING IDEA
-----------------------------------------------------------

Let dp[e][f] represent the minimum number of egg droppings
required in the worst case to determine the highest safe
floor when we have:

    e = number of eggs
    f = number of floors

Suppose we drop an egg from floor x.

There are two possible cases:

1. The egg BREAKS:

       We now have e - 1 eggs and x - 1 floors below.

       Cost = dp[e - 1][x - 1]

2. The egg DOES NOT BREAK:

       We still have e eggs and f - x floors above.

       Cost = dp[e][f - x]

Since we need a guaranteed answer, we consider the WORST
of these two cases.

Therefore:

    dp[e][f] =
        1 + min over x { max(dp[e-1][x-1],
                             dp[e][f-x]) }


Base cases:

    dp[e][0] = 0
    dp[e][1] = 1

With only one egg:

    dp[1][f] = f

For the given problem:

    E = 2
    F = 100

The minimum number of droppings guaranteed is:

    14


-----------------------------------------------------------
COMPLEXITY ANALYSIS
-----------------------------------------------------------

Time Complexity  : O(E * F^2)

Space Complexity : O(E * F)

The DP table contains E * F states.

For every state dp[e][f], all possible floors x from
1 to f are checked.

Therefore:

    Time  = O(E * F^2)
    Space = O(E * F)

For E = 2 and F = 100, the algorithm is easily manageable.


===========================================================
*/

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int eggDrop(int eggs, int floors)
{
    /*
        Allocate the DP table.

        dp[e][f] = minimum number of attempts required
                   with e eggs and f floors.
    */
    int **dp = (int **)malloc((eggs + 1) * sizeof(int *));

    if (dp == NULL)
    {
        printf("Memory allocation failed.\n");
        return -1;
    }

    for (int i = 0; i <= eggs; i++)
    {
        dp[i] = (int *)malloc((floors + 1) * sizeof(int));

        if (dp[i] == NULL)
        {
            printf("Memory allocation failed.\n");

            for (int j = 0; j < i; j++)
                free(dp[j]);

            free(dp);
            return -1;
        }
    }

    /*
        Base case:
        0 floors require 0 attempts.
    */
    for (int e = 1; e <= eggs; e++)
    {
        dp[e][0] = 0;
    }

    /*
        Base case:
        1 floor requires 1 attempt.
    */
    for (int e = 1; e <= eggs; e++)
    {
        dp[e][1] = 1;
    }

    /*
        Base case:
        With only one egg, we must test every floor
        sequentially.
    */
    for (int f = 1; f <= floors; f++)
    {
        dp[1][f] = f;
    }

    /*
        Fill the DP table.
    */
    for (int e = 2; e <= eggs; e++)
    {
        for (int f = 2; f <= floors; f++)
        {
            dp[e][f] = 1000000;

            /*
                Try dropping the egg from every possible floor.
            */
            for (int x = 1; x <= f; x++)
            {
                int broken = dp[e - 1][x - 1];

                int notBroken = dp[e][f - x];

                int attempts = 1 + max(broken, notBroken);

                if (attempts < dp[e][f])
                {
                    dp[e][f] = attempts;
                }
            }
        }
    }

    int result = dp[eggs][floors];

    /*
        Free allocated memory.
    */
    for (int i = 0; i <= eggs; i++)
    {
        free(dp[i]);
    }

    free(dp);

    return result;
}

int main()
{
    int eggs, floors;

    printf("Enter number of eggs: ");
    scanf("%d", &eggs);

    printf("Enter number of floors: ");
    scanf("%d", &floors);

    if (eggs <= 0 || floors < 0)
    {
        printf("Invalid input.\n");
        return 1;
    }

    int result = eggDrop(eggs, floors);

    printf("\nMinimum number of droppings required = %d\n",
           result);

    return 0;
}