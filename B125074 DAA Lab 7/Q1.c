#include <stdio.h>
#include <stdlib.h>

/*
===========================================================
QUESTION 1: INVERT THE COIN-TRIANGLE
===========================================================

Consider an equilateral triangle formed by closely packed
coins. Design an algorithm to flip the triangle upside down
in the minimum number of moves, where one coin can be slid
at a time to its new position.

Give a compact formula for the minimum number of moves.


-----------------------------------------------------------
PSEUDOCODE
-----------------------------------------------------------

INVERT_TRIANGLE(N)

    coins = N * (N + 1) / 2

    overlap = floor(N / 2)

    minimumMoves = coins - overlap

    return minimumMoves


MAIN

    Read N

    result = INVERT_TRIANGLE(N)

    Display result


-----------------------------------------------------------
ALGORITHM / IDEA
-----------------------------------------------------------

Let N be the number of rows in the original triangle.

The total number of coins in an N-row triangle is:

    coins = N(N + 1) / 2

When the triangle is inverted, some coin positions are
common to both the original and inverted triangles.

The maximum number of coins that can remain in their
positions is:

    overlap = floor(N / 2)

Every other coin has to be moved once.

Therefore, the minimum number of moves is:

    M(N) = N(N + 1) / 2 - floor(N / 2)

This is the compact formula for the answer.


For example:

    N = 3

    Total coins = 3(4)/2 = 6
    Maximum overlap = floor(3/2) = 1

    Minimum moves = 6 - 1 = 5


-----------------------------------------------------------
COMPLEXITY ANALYSIS
-----------------------------------------------------------

Time Complexity  : O(1)

Space Complexity : O(1)

The minimum number of moves is obtained directly from
the compact formula, so no iteration over the coins is
required.

===========================================================
*/

long long invertTriangle(int n)
{
    /*
        Calculate the total number of coins.
    */
    long long coins = (long long)n * (n + 1) / 2;

    /*
        Calculate the number of overlapping positions.
    */
    long long overlap = n / 2;

    /*
        Remaining coins must be moved.
    */
    long long minimumMoves = coins - overlap;

    return minimumMoves;
}

int main()
{
    int n;

    printf("Enter number of rows n: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("n must be a positive integer.\n");
        return 1;
    }

    long long result = invertTriangle(n);

    printf("The minimum number of moves = %lld\n", result);

    printf("\nFormula:\n");
    printf("M(n) = n(n + 1)/2 - floor(n/2)\n");

    return 0;
}