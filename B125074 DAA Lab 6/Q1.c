#include <stdio.h>
#include <stdlib.h>

/*
===========================================================
QUESTION 1: FIBONACCI NUMBER USING DYNAMIC PROGRAMMING
===========================================================

Write a program to find the nth Fibonacci number using
Dynamic Programming.


-----------------------------------------------------------
PSEUDOCODE
-----------------------------------------------------------

FIBONACCI(N)

    if N == 0
        return 0

    if N == 1
        return 1

    Create array dp[N + 1]

    dp[0] = 0
    dp[1] = 1

    for i = 2 to N

        dp[i] = dp[i - 1] + dp[i - 2]

    return dp[N]


MAIN

    Read N

    result = FIBONACCI(N)

    Display result


-----------------------------------------------------------
DYNAMIC PROGRAMMING IDEA
-----------------------------------------------------------

The Fibonacci sequence is:

    F(0) = 0
    F(1) = 1

    F(N) = F(N-1) + F(N-2)

Instead of calculating the same values repeatedly,
Dynamic Programming stores previously calculated values
in an array.

Therefore, each Fibonacci number is calculated only once.


-----------------------------------------------------------
COMPLEXITY ANALYSIS
-----------------------------------------------------------

Time Complexity  : O(N)

Space Complexity : O(N)

The algorithm calculates values from F(0) to F(N)
exactly once and stores them in the DP array.

===========================================================
*/

int fibonacci(int n)
{
    /*
        Allocate memory for the DP table.
    */
    int *dp = (int *)malloc((n + 1) * sizeof(int));

    if (dp == NULL)
    {
        printf("Memory allocation failed.\n");
        return -1;
    }

    /*
        Base cases.
    */
    dp[0] = 0;

    if (n >= 1)
    {
        dp[1] = 1;
    }

    /*
        Fill the DP table from bottom to top.
    */
    for (int i = 2; i <= n; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    int result = dp[n];

    free(dp);

    return result;
}

int main()
{
    int n;

    printf("Enter n: ");
    scanf("%d", &n);

    if (n < 0)
    {
        printf("n must be non-negative.\n");
        return 1;
    }

    int result = fibonacci(n);

    printf("The %dth Fibonacci number = %d\n", n, result);

    return 0;
}