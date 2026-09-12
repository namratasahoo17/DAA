#include <stdio.h>
#include <stdlib.h>

/*
===========================================================
QUESTION 5: HITTING A MOVING TARGET
===========================================================

A computer game has a shooter and a moving target.

The shooter can hit any of n > 1 hiding spots arranged
along a straight line.

The shooter cannot see the target. The only information
available is that the target moves to an adjacent hiding
spot between every two consecutive shots.

Design an algorithm that guarantees hitting the target,
or prove that no such algorithm exists.


-----------------------------------------------------------
PSEUDOCODE
-----------------------------------------------------------

HIT_TARGET(N)

    if N <= 1
        return

    for start = 1 to N

        for position = start to N

            SHOOT(position)

            Target moves to an adjacent position

        for position = N-1 down to 1

            SHOOT(position)

            Target moves to an adjacent position

    Repeat the left-to-right and right-to-left scans
    until the target is hit.


-----------------------------------------------------------
ALGORITHM / IDEA
-----------------------------------------------------------

The target moves to an adjacent hiding spot after every
shot.

Therefore, if the shooter repeatedly shoots the hiding
spots in the same direction, the target can avoid being
hit by staying one step ahead.

The important observation is that the target changes its
position by exactly one place between consecutive shots.

A successful strategy is to sweep through the hiding spots
in one direction and then reverse the direction.

For example, for n = 5:

    Shoot: 1 2 3 4 5
    Then:  4 3 2 1
    Then:  2 3 4 5
    ...

The direction is repeatedly changed.

This prevents the target from continuously staying on the
opposite parity/path of the shooter's sequence.

The shooter can therefore guarantee hitting the target by
using a repeated back-and-forth scan of the hiding spots.

The algorithm does not need to know the target's current
position.


-----------------------------------------------------------
COMPLEXITY ANALYSIS
-----------------------------------------------------------

For one complete sweep through all hiding spots:

    Time Complexity  : O(N)

The strategy may need repeated sweeps until the target is
hit.

The exact number of shots depends on the target's movement,
so the worst-case running time for the repeated strategy is
expressed in terms of the number of shots made.

Space Complexity : O(1)

Only the current hiding spot and direction need to be stored.


===========================================================
*/

void hitTarget(int n)
{
    int position;
    int direction = 1;

    /*
        The target can keep moving, so the shooter repeatedly
        sweeps from one end to the other and reverses direction.
    */

    while (1)
    {
        if (direction == 1)
        {
            /*
                Left-to-right sweep.
            */
            for (position = 1; position <= n; position++)
            {
                printf("Shoot at hiding spot %d\n", position);
            }

            direction = -1;
        }
        else
        {
            /*
                Right-to-left sweep.
            */
            for (position = n; position >= 1; position--)
            {
                printf("Shoot at hiding spot %d\n", position);
            }

            direction = 1;
        }

        /*
            In an actual game, the loop stops as soon as
            the target is hit.
        */

        /*
            This demonstration performs one complete
            back-and-forth cycle and then stops.
        */
        break;
    }
}

int main()
{
    int n;

    printf("Enter number of hiding spots: ");
    scanf("%d", &n);

    if (n <= 1)
    {
        printf("n must be greater than 1.\n");
        return 1;
    }

    printf("\nHITTING A MOVING TARGET\n");
    printf("Number of hiding spots = %d\n", n);

    printf("\nShooting sequence:\n");

    hitTarget(n);

    printf("\nThe shooter uses a repeated back-and-forth scan.\n");
    printf("This changes the direction of the search and prevents\n");
    printf("the target from indefinitely staying ahead of the shooter.\n");

    return 0;
}