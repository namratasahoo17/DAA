#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*
===========================================================
QUESTION 4: MATRIX CHAIN MULTIPLICATION
===========================================================

Write a program to implement Matrix Chain Multiplication
using Dynamic Programming.

Given the dimensions of N-1 matrices in an array arr[],
determine the minimum number of scalar multiplications
required to multiply the complete matrix chain.


EXAMPLE:

Input:
    N = 4
    arr[] = {10, 30, 5, 60}

Matrices:
    A1 = 10 x 30
    A2 = 30 x 5
    A3 = 5 x 60

Output:
    4500

Time Complexity:
    O(N^3)

Space Complexity:
    O(N^2)


===========================================================
PSEUDOCODE
===========================================================

MATRIX_CHAIN(arr, N)

    Number of matrices = N - 1

    Create DP table dp[N][N]

    for i = 1 to N-1
        dp[i][i] = 0

    for chainLength = 2 to N-1

        for i = 1 to N-chainLength

            j = i + chainLength - 1

            dp[i][j] = infinity

            for k = i to j-1

                cost =
                    dp[i][k]
                    + dp[k+1][j]
                    + arr[i-1] * arr[k] * arr[j]

                if cost < dp[i][j]

                    dp[i][j] = cost

    return dp[1][N-1]


===========================================================
COMPLEXITY ANALYSIS
===========================================================

There are O(N^2) subproblems.

For every subproblem, we try O(N) possible
split positions.

Therefore:

    Time Complexity = O(N^3)

The DP table requires:

    Space Complexity = O(N^2)

===========================================================
*/

int main()
{
    int N;

    printf("Enter N: ");
    scanf("%d", &N);

    /*
        N dimensions represent N-1 matrices.

        Example:

        N = 4

        arr = {10, 30, 5, 60}

        represents:

        A1 = 10 x 30
        A2 = 30 x 5
        A3 = 5 x 60
    */

    if (N < 2)
    {
        printf("N must be at least 2.\n");
        return 1;
    }

    int *arr = (int *)malloc(N * sizeof(int));

    if (arr == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d dimensions:\n", N);

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &arr[i]);
    }

    /*
        dp[i][j] stores the minimum number of scalar
        multiplications required to multiply matrices
        Ai through Aj.
    */

    long long **dp =
        (long long **)malloc(N * sizeof(long long *));

    if (dp == NULL)
    {
        printf("Memory allocation failed.\n");
        free(arr);
        return 1;
    }

    for (int i = 0; i < N; i++)
    {
        dp[i] =
            (long long *)malloc(N * sizeof(long long));

        if (dp[i] == NULL)
        {
            printf("Memory allocation failed.\n");

            for (int j = 0; j < i; j++)
            {
                free(dp[j]);
            }

            free(dp);
            free(arr);

            return 1;
        }
    }

    /*
        A single matrix requires zero multiplications.

        Therefore:

            dp[i][i] = 0
    */

    for (int i = 1; i < N; i++)
    {
        dp[i][i] = 0;
    }

    /*
        chainLength represents the number of matrices
        in the current subchain.

        We start with 2 matrices, then 3, then 4, etc.
    */

    for (int chainLength = 2;
         chainLength <= N - 1;
         chainLength++)
    {
        /*
            i represents the starting matrix.
        */

        for (int i = 1;
             i <= N - chainLength;
             i++)
        {
            /*
                j represents the ending matrix.
            */

            int j = i + chainLength - 1;

            /*
                Initially assume that the cost is
                extremely large.
            */

            dp[i][j] = LLONG_MAX;

            /*
                Try every possible position to split
                the matrix chain.

                Left side:
                    Ai ... Ak

                Right side:
                    A(k+1) ... Aj
            */

            for (int k = i; k < j; k++)
            {
                /*
                    Total cost consists of:

                    1. Cost of multiplying left chain
                    2. Cost of multiplying right chain
                    3. Cost of multiplying the two
                       resulting matrices
                */

                long long cost =
                    dp[i][k]
                    +
                    dp[k + 1][j]
                    +
                    (long long)arr[i - 1]
                    * arr[k]
                    * arr[j];

                /*
                    Keep the minimum cost.
                */

                if (cost < dp[i][j])
                {
                    dp[i][j] = cost;
                }
            }
        }
    }

    /*
        dp[1][N-1] contains the minimum number of
        scalar multiplications required to multiply
        the complete matrix chain.
    */

    printf("\nMinimum number of scalar multiplications = %lld\n",
           dp[1][N - 1]);

    /*
        Free dynamically allocated memory.
    */

    for (int i = 0; i < N; i++)
    {
        free(dp[i]);
    }

    free(dp);
    free(arr);

    return 0;
}
