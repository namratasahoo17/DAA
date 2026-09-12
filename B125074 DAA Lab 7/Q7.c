#include <stdio.h>
#include <stdlib.h>

/*
===========================================================
QUESTION 7: MATRIX CHAIN MULTIPLICATION (MCM)
===========================================================

Consider the Matrix Chain Multiplication problem.

Write a program in C to implement the Dynamic Programming
solution of the MCM problem in order to find:

    1. The minimum number of scalar multiplications.
    2. The corresponding ordering of matrix multiplication.

If there are N matrices:

    A1, A2, A3, ..., AN

and their dimensions are given by:

    p0 x p1
    p1 x p2
    ...
    p(N-1) x pN

then the dimension array is:

    p[0], p[1], ..., p[N]


-----------------------------------------------------------
PSEUDOCODE
-----------------------------------------------------------

MATRIX_CHAIN_ORDER(P, N)

    Create table M[N][N]
    Create table S[N][N]

    for i = 1 to N
        M[i][i] = 0

    for length = 2 to N

        for i = 1 to N - length + 1

            j = i + length - 1

            M[i][j] = infinity

            for k = i to j - 1

                cost = M[i][k]
                     + M[k+1][j]
                     + P[i-1] * P[k] * P[j]

                if cost < M[i][j]

                    M[i][j] = cost
                    S[i][j] = k

    return M[1][N]


PRINT_OPTIMAL_PARENTHESES(S, i, j)

    if i == j
        print A[i]
        return

    print "("

    PRINT_OPTIMAL_PARENTHESES(S, i, S[i][j])

    PRINT_OPTIMAL_PARENTHESES(S, S[i][j] + 1, j)

    print ")"


MAIN

    Read N

    Read dimensions P[0] to P[N]

    result = MATRIX_CHAIN_ORDER(P, N)

    Display result

    PRINT_OPTIMAL_PARENTHESES(S, 1, N)


-----------------------------------------------------------
DYNAMIC PROGRAMMING IDEA
-----------------------------------------------------------

Matrix multiplication is associative.

Therefore:

    (A1 A2) A3

and

    A1 (A2 A3)

produce the same final matrix, but the number of scalar
multiplications can be different.

For example, if:

    A = 10 x 30
    B = 30 x 5
    C = 5 x 60

Then:

    (AB)C

requires:

    10 * 30 * 5 + 10 * 5 * 60
    = 1500 + 3000
    = 4500

while:

    A(BC)

requires:

    30 * 5 * 60 + 10 * 30 * 60
    = 9000 + 18000
    = 27000

So, the order of multiplication matters.

Let:

    M[i][j]

be the minimum number of scalar multiplications required
to multiply matrices Ai through Aj.

Base case:

    M[i][i] = 0

because a single matrix requires no multiplication.

For a chain Ai ... Aj, split the chain at matrix Ak.

The cost is:

    M[i][k]
    + M[k+1][j]
    + P[i-1] * P[k] * P[j]

Therefore:

    M[i][j] =
        min over i <= k < j of

        M[i][k] + M[k+1][j]
        + P[i-1] * P[k] * P[j]

The S table stores the value of k that gives the minimum
cost.

This allows us to reconstruct the optimal parenthesization.


-----------------------------------------------------------
COMPLEXITY ANALYSIS
-----------------------------------------------------------

There are O(N^2) subproblems.

For every subproblem, all possible split points k are
checked.

Therefore:

    Time Complexity  : O(N^3)

    Space Complexity : O(N^2)

The M table and S table both require O(N^2) space.


===========================================================
*/

#define MAX_MATRICES 100


/*
-----------------------------------------------------------
Print the optimal parenthesization.

S[i][j] stores the best position at which the chain
Ai ... Aj should be divided.
-----------------------------------------------------------
*/

void printOptimalParentheses(
    int S[MAX_MATRICES][MAX_MATRICES],
    int i,
    int j)
{
    if (i == j)
    {
        printf("A%d", i);
        return;
    }

    printf("(");

    /*
        Print left part.
    */
    printOptimalParentheses(
        S,
        i,
        S[i][j]
    );

    /*
        Print right part.
    */
    printOptimalParentheses(
        S,
        S[i][j] + 1,
        j
    );

    printf(")");
}


/*
-----------------------------------------------------------
Matrix Chain Multiplication using Dynamic Programming.
-----------------------------------------------------------
*/

long long matrixChainMultiplication(
    int p[],
    int n,
    int S[MAX_MATRICES][MAX_MATRICES])
{
    /*
        M[i][j] stores minimum scalar multiplications
        required to multiply Ai through Aj.
    */
    long long M[MAX_MATRICES][MAX_MATRICES];

    /*
        Base case:
        One matrix requires zero multiplications.
    */
    for (int i = 1; i <= n; i++)
    {
        M[i][i] = 0;
    }

    /*
        length represents the number of matrices
        in the current chain.
    */
    for (int length = 2; length <= n; length++)
    {
        for (int i = 1;
             i <= n - length + 1;
             i++)
        {
            int j = i + length - 1;

            /*
                Initialize with a very large value.
            */
            M[i][j] = 9223372036854775807LL;

            /*
                Try every possible split point.
            */
            for (int k = i; k < j; k++)
            {
                long long cost =
                    M[i][k]
                    + M[k + 1][j]
                    + (long long)p[i - 1]
                    * p[k]
                    * p[j];

                if (cost < M[i][j])
                {
                    M[i][j] = cost;

                    /*
                        Store the optimal split point.
                    */
                    S[i][j] = k;
                }
            }
        }
    }

    return M[1][n];
}


int main()
{
    int n;

    printf("Enter number of matrices: ");
    scanf("%d", &n);

    if (n <= 0 || n >= MAX_MATRICES)
    {
        printf("Invalid number of matrices.\n");
        return 1;
    }

    /*
        p contains n+1 dimensions.

        Example:

        A1 = 10 x 30
        A2 = 30 x 5
        A3 = 5 x 60

        p = {10, 30, 5, 60}
    */
    int p[MAX_MATRICES];

    printf("\nEnter the dimensions array P:\n");

    printf("Enter %d values:\n", n + 1);

    for (int i = 0; i <= n; i++)
    {
        scanf("%d", &p[i]);

        if (p[i] <= 0)
        {
            printf("Dimensions must be positive.\n");
            return 1;
        }
    }

    /*
        S table stores the optimal split points.
    */
    int S[MAX_MATRICES][MAX_MATRICES] = {0};

    /*
        Calculate minimum scalar multiplications.
    */
    long long result =
        matrixChainMultiplication(
            p,
            n,
            S
        );

    printf("\nMATRIX CHAIN MULTIPLICATION\n");

    printf("Number of matrices = %d\n", n);

    printf("Minimum number of scalar multiplications = %lld\n",
           result);

    /*
        Print the optimal ordering.
    */
    printf("Optimal parenthesization = ");

    printOptimalParentheses(
        S,
        1,
        n
    );

    printf("\n");

    return 0;
}