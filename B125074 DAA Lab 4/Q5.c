// Application of sorting-V: Given a list I of n intervals, specified as (xi,yi) pairs, return a list where the overlapping intervals are merged. For I = {(1,3),(2,6),(8,10),(7,18)} the output should be {(1,6),(7,18)}. Your algorithm should run in worst-case O(n·logn) time complexity. By choosing a suitable input and output representation, write a program in C to validate your algorithm.

/* ALGORITHM MergeIntervals(I, n)

    Sort I by start time

    Initialize an empty list M

    FOR i = 1 TO n DO
        IF M is empty OR M.last.end < I[i].start THEN
            Append I[i] to M
        ELSE
            M.last.end = max(M.last.end, I[i].end)
        END IF
    END FOR

    OUTPUT M

END ALGORITHM */


#include <stdio.h>

/* ---------------------------------------------------------
   Interval structure
   --------------------------------------------------------- */

struct Interval
{
    int start;
    int end;
};

/* ---------------------------------------------------------
   Merge two parts
   --------------------------------------------------------- */

void merge(struct Interval arr[],
           int left,
           int mid,
           int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    struct Interval L[n1];
    struct Interval R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0;
    int j = 0;
    int k = left;

    /*
        Sort according to start time.
    */

    while (i < n1 && j < n2)
    {
        if (L[i].start <= R[j].start)
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

void mergeSort(struct Interval arr[],
               int left,
               int right)
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
    printf("       MERGE OVERLAPPING INTERVALS\n");
    printf("========================================\n");

    printf("\nEnter number of intervals: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Number of intervals must be positive.\n");
        return 0;
    }

    struct Interval intervals[n];

    /*
        Input intervals.
    */

    printf("\nEnter the intervals:\n");

    for (int i = 0; i < n; i++)
    {
        printf("\nInterval %d start: ", i + 1);
        scanf("%d", &intervals[i].start);

        printf("Interval %d end: ", i + 1);
        scanf("%d", &intervals[i].end);

        if (intervals[i].start > intervals[i].end)
        {
            printf("Invalid interval.\n");
            printf("Start must be less than or equal to end.\n");
            return 0;
        }
    }

    /*
        Sort intervals by start time.
    */

    mergeSort(intervals, 0, n - 1);

    printf("\n========================================\n");
    printf("          SORTED INTERVALS\n");
    printf("========================================\n");

    for (int i = 0; i < n; i++)
    {
        printf("(%d, %d)\n",
               intervals[i].start,
               intervals[i].end);
    }

    /*
        Merge overlapping intervals.
    */

    struct Interval result[n];

    int count = 0;

    result[0] = intervals[0];
    count = 1;

    printf("\n========================================\n");
    printf("             ANALYSIS\n");
    printf("========================================\n");

    for (int i = 1; i < n; i++)
    {
        /*
            Check whether the current interval overlaps
            with the last interval in the result.
        */

        if (intervals[i].start <= result[count - 1].end)
        {
            printf("\nOverlapping intervals:\n");

            printf("(%d, %d) and (%d, %d)\n",
                   result[count - 1].start,
                   result[count - 1].end,
                   intervals[i].start,
                   intervals[i].end);

            /*
                Extend the ending point if necessary.
            */

            if (intervals[i].end >
                result[count - 1].end)
            {
                result[count - 1].end =
                    intervals[i].end;
            }

            printf("Merged into: (%d, %d)\n",
                   result[count - 1].start,
                   result[count - 1].end);
        }
        else
        {
            /*
                No overlap.
                Add the interval separately.
            */

            printf("\nNo overlap:\n");

            printf("(%d, %d) is kept separately.\n",
                   intervals[i].start,
                   intervals[i].end);

            result[count] = intervals[i];
            count++;
        }
    }

    /*
        Final output.
    */

    printf("\n========================================\n");
    printf("              RESULT\n");
    printf("========================================\n");

    printf("Merged intervals:\n");

    for (int i = 0; i < count; i++)
    {
        printf("(%d, %d)\n",
               result[i].start,
               result[i].end);
    }

    /*
        Complexity analysis.
    */

    printf("\n========================================\n");
    printf("          COMPLEXITY ANALYSIS\n");
    printf("========================================\n");

    printf("Sorting intervals = O(n log n)\n");
    printf("Merging intervals  = O(n)\n");
    printf("Overall             = O(n log n)\n");

    return 0;
}
