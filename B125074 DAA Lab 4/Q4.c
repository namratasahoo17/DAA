// Application of sorting-IV: A camera at the door tracks the entry time ai and exit time bi (assume bi > ai) for each of n the persons pi attending a party. Give an O(n·logn) algorithm that analyses this data to determine the time when the most people were simultaneously present at the party. Assume that all entry and exit times are distinct (no ties). By choosing the proper input representation, write a program in C to validate your algorithm.

/* ALGORITHM MaxSimultaneousPresence(a, b, n)

    Create an empty list of events

    FOR i = 1 TO n DO
        Add (a[i], "entry") to events
        Add (b[i], "exit") to events
    END FOR

    Sort events by time

    Initialize currentCount = 0
    Initialize maxCount = 0
    Initialize maxTime = 0

    FOR each event in events DO
        IF event is "entry" THEN
            currentCount++
            IF currentCount > maxCount THEN
                maxCount = currentCount
                maxTime = event.time
            END IF
        ELSE IF event is "exit" THEN
            currentCount--
        END IF
    END FOR

    OUTPUT maxTime, maxCount

END ALGORITHM */


#include <stdio.h>

struct Event
{
    int time;
    int type;       /* 1 = entry, -1 = exit */
};

/* ---------------------------------------------------------
   Merge
   --------------------------------------------------------- */

void merge(struct Event arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    struct Event L[n1];
    struct Event R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        if (L[i].time <= R[j].time)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }

        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* ---------------------------------------------------------
   Merge Sort
   --------------------------------------------------------- */

void mergeSort(struct Event arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

/* ---------------------------------------------------------
   Main
   --------------------------------------------------------- */

int main()
{
    int n;

    printf("========================================\n");
    printf("       MAXIMUM PEOPLE PRESENT\n");
    printf("========================================\n");

    printf("\nEnter number of people: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Number of people must be positive.\n");
        return 0;
    }

    struct Event events[2 * n];

    printf("\nEnter entry and exit times:\n");

    for (int i = 0; i < n; i++)
    {
        int entry;
        int exit;

        printf("\nPerson %d entry time: ", i + 1);
        scanf("%d", &entry);

        printf("Person %d exit time: ", i + 1);
        scanf("%d", &exit);

        if (entry >= exit)
        {
            printf("Invalid interval.\n");
            printf("Entry time must be less than exit time.\n");
            return 0;
        }

        events[2 * i].time = entry;
        events[2 * i].type = 1;

        events[2 * i + 1].time = exit;
        events[2 * i + 1].type = -1;
    }

    /* -----------------------------------------------------
       Sort all events by time
       ----------------------------------------------------- */

    mergeSort(events, 0, 2 * n - 1);

    printf("\n========================================\n");
    printf("          SORTED EVENTS\n");
    printf("========================================\n");

    for (int i = 0; i < 2 * n; i++)
    {
        if (events[i].type == 1)
            printf("Time %d : Entry\n", events[i].time);
        else
            printf("Time %d : Exit\n", events[i].time);
    }

    /* -----------------------------------------------------
       Sweep through events

       Events at the same time are processed together.
       ----------------------------------------------------- */

    int people = 0;
    int maxPeople = 0;
    int maxTime = 0;

    printf("\n========================================\n");
    printf("             ANALYSIS\n");
    printf("========================================\n");

    int i = 0;

    while (i < 2 * n)
    {
        int currentTime = events[i].time;

        int entries = 0;
        int exits = 0;

        /*
            Count all events at the same time.
        */

        while (i < 2 * n &&
               events[i].time == currentTime)
        {
            if (events[i].type == 1)
                entries++;
            else
                exits++;

            i++;
        }

        /*
            People who were already present leave first.
        */

        people -= exits;

        /*
            Then new people enter.
        */

        people += entries;

        printf("\nTime %d:\n", currentTime);
        printf("  Entries = %d\n", entries);
        printf("  Exits   = %d\n", exits);
        printf("  People present = %d\n", people);

        /*
            Update maximum.
        */

        if (people > maxPeople)
        {
            maxPeople = people;
            maxTime = currentTime;
        }
    }

    /* -----------------------------------------------------
       Result
       ----------------------------------------------------- */

    printf("\n========================================\n");
    printf("              RESULT\n");
    printf("========================================\n");

    printf("Maximum people present = %d\n", maxPeople);
    printf("Time = %d\n", maxTime);

    /* -----------------------------------------------------
       Complexity
       ----------------------------------------------------- */

    printf("\n========================================\n");
    printf("          COMPLEXITY ANALYSIS\n");
    printf("========================================\n");

    printf("Number of events = 2n = O(n)\n");
    printf("Sorting events   = O(n log n)\n");
    printf("Scanning events  = O(n)\n");
    printf("Overall          = O(n log n)\n");

    return 0;
}