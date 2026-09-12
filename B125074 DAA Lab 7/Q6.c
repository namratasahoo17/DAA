#include <stdio.h>
#include <stdlib.h>

/*
===========================================================
QUESTION 6: THE BEST TIME TO BE ALIVE
===========================================================

An editor wants to find the time when the largest number
of prominent scientists were alive.

The input is the book's index. Each entry contains:

    - Birth year
    - Death year

The entries are sorted alphabetically.

If one scientist died in the same year another scientist
was born, assume that the death happened before the birth.

Design an algorithm to find the year when the maximum
number of scientists were alive.


-----------------------------------------------------------
PSEUDOCODE
-----------------------------------------------------------

BEST_TIME(scientists, N)

    Create an array of events

    for each scientist i

        Create a BIRTH event with:
            year = birth[i]
            type = BIRTH

        Create a DEATH event with:
            year = death[i]
            type = DEATH

    Sort all events by year

    If two events have the same year:
        DEATH comes before BIRTH

    current = 0
    maximum = 0
    bestYear = 0

    for each event

        if event is DEATH
            current = current - 1

        else if event is BIRTH
            current = current + 1

            if current > maximum
                maximum = current
                bestYear = event.year

    return bestYear


MAIN

    Read N

    Read birth and death years

    result = BEST_TIME(scientists, N)

    Display result and maximum number alive


-----------------------------------------------------------
ALGORITHM / IDEA
-----------------------------------------------------------

For every scientist, create two events:

    Birth  -> +1 scientist
    Death  -> -1 scientist

Sort all events according to year.

The events must be processed in this order when two events
have the same year:

    DEATH before BIRTH

This follows the condition given in the question that if
one person dies in the same year another person is born,
the death occurs first.

Maintain a variable:

    current = number of scientists currently alive

Whenever a birth occurs:

    current = current + 1

Whenever a death occurs:

    current = current - 1

Whenever current becomes greater than the previous maximum,
store that year as the best year.

The final result is the year in which the maximum number
of scientists were alive.


Example:

    Scientist 1: 1900 - 1950
    Scientist 2: 1910 - 1960
    Scientist 3: 1920 - 1970

Events:

    1900  Birth
    1910  Birth
    1920  Birth
    1950  Death
    1960  Death
    1970  Death

Number alive:

    1900 -> 1
    1910 -> 2
    1920 -> 3
    1950 -> 2
    1960 -> 1
    1970 -> 0

Therefore:

    Best time = 1920
    Maximum alive = 3


-----------------------------------------------------------
COMPLEXITY ANALYSIS
-----------------------------------------------------------

There are 2N events.

Creating the events takes:

    O(N)

Sorting the events takes:

    O(N log N)

Scanning the events takes:

    O(N)

Therefore:

    Time Complexity  : O(N log N)

    Space Complexity : O(N)

The O(N log N) time is dominated by sorting the events.


===========================================================
*/

typedef struct
{
    int year;
    int type;
    /*
        type = 0 -> DEATH
        type = 1 -> BIRTH

        Death is given lower priority so that when two
        events have the same year, death is processed first.
    */
} Event;


/*
-----------------------------------------------------------
Comparison function for sorting events.

Events are sorted by:

    1. Year
    2. Death before Birth if years are equal
-----------------------------------------------------------
*/

int compareEvents(const void *a, const void *b)
{
    Event *event1 = (Event *)a;
    Event *event2 = (Event *)b;

    if (event1->year != event2->year)
    {
        return event1->year - event2->year;
    }

    /*
        Same year:
        Death (0) comes before Birth (1).
    */
    return event1->type - event2->type;
}


/*
-----------------------------------------------------------
Find the year in which the maximum number of scientists
were alive.
-----------------------------------------------------------
*/

int bestTime(int birth[], int death[], int n, int *maximum)
{
    /*
        Each scientist creates two events.
    */
    Event *events =
        (Event *)malloc(2 * n * sizeof(Event));

    if (events == NULL)
    {
        printf("Memory allocation failed.\n");
        return -1;
    }

    /*
        Create birth and death events.
    */
    for (int i = 0; i < n; i++)
    {
        /*
            Birth event.
        */
        events[2 * i].year = birth[i];
        events[2 * i].type = 1;

        /*
            Death event.
        */
        events[2 * i + 1].year = death[i];
        events[2 * i + 1].type = 0;
    }

    /*
        Sort all events.
    */
    qsort(events, 2 * n, sizeof(Event), compareEvents);

    int current = 0;
    *maximum = 0;

    int bestYear = 0;

    /*
        Process all events.
    */
    for (int i = 0; i < 2 * n; i++)
    {
        if (events[i].type == 0)
        {
            /*
                Scientist dies.
            */
            current--;
        }
        else
        {
            /*
                Scientist is born.
            */
            current++;

            /*
                Update maximum after processing the birth.
            */
            if (current > *maximum)
            {
                *maximum = current;
                bestYear = events[i].year;
            }
        }
    }

    free(events);

    return bestYear;
}


int main()
{
    int n;

    printf("Enter number of scientists: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Number of scientists must be positive.\n");
        return 1;
    }

    int *birth =
        (int *)malloc(n * sizeof(int));

    int *death =
        (int *)malloc(n * sizeof(int));

    if (birth == NULL || death == NULL)
    {
        printf("Memory allocation failed.\n");

        free(birth);
        free(death);

        return 1;
    }

    /*
        Read birth and death years.
    */
    printf("\nEnter birth year and death year for each scientist:\n");

    for (int i = 0; i < n; i++)
    {
        printf("Scientist %d: ", i + 1);
        scanf("%d %d", &birth[i], &death[i]);

        if (death[i] < birth[i])
        {
            printf("Invalid years.\n");

            free(birth);
            free(death);

            return 1;
        }
    }

    int maximum;

    int year = bestTime(
        birth,
        death,
        n,
        &maximum
    );

    if (year == -1)
    {
        free(birth);
        free(death);

        return 1;
    }

    printf("\nTHE BEST TIME TO BE ALIVE\n");
    printf("Year with maximum scientists alive = %d\n", year);
    printf("Maximum number of scientists alive = %d\n",
           maximum);

    free(birth);
    free(death);

    return 0;
}