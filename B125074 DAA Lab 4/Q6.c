// Application of sorting-VI: You are given a set S of n intervals on a line, with the ith interval described by its left and right endpoints (li,ri). Give an O(n · logn) algorithm to identify a point p on the line that is in the largest number of intervals. As an example, for S ={(10,40),(20,60),(50,90),(15,70)} no point exists in all four intervals, but p = 50 is an example of a point in three intervals. You can assume an endpoint counts as being in its interval. By choosing a suitable input and output representation, write a program in C to validate your algorithm.

/* ALGORITHM FindMaxIntersectionPoint(S, n)

    Create a list of events: (li, +1) and (ri, -1)

    Sort events by x-coordinate

    Initialize max_count = 0 and current_count = 0

    FOR each event DO
        current_count += event.value
        IF current_count > max_count THEN
            max_count = current_count
        END IF
    END FOR

    OUTPUT max_count

END ALGORITHM */

#include <stdio.h>

/* ---------------------------------------------------------
   Event structure
   --------------------------------------------------------- */

struct Event
{
    int point;
    int type;       /* +1 = start, -1 = end */
};

/* ---------------------------------------------------------
   Merge
   --------------------------------------------------------- */

void merge(struct Event arr[],
           int left,
           int mid,
           int right)
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

    /*
        Sort by point.

        If two events have the same point,
        start (+1) comes before end (-1).

        This is important because endpoints count
        as being inside an interval.
    */

    while (i < n1 && j < n2)
    {
        if (L[i].point < R[j].point ||
            (L[i].point == R[j].point &&
             L[i].type > R[j].type))
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

void mergeSort(struct Event arr[],
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
    printf("     MAXIMUM INTERVAL COVERAGE\n");
    printf("========================================\n");

    printf("\nEnter number of intervals: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Number of intervals must be positive.\n");
        return 0;
    }

    struct Event events[2 * n];

    /*
        Input intervals.
    */

    printf("\nEnter the intervals:\n");

    for (int i = 0; i < n; i++)
    {
        int start;
        int end;

        printf("\nInterval %d start: ", i + 1);
        scanf("%d", &start);

        printf("Interval %d end: ", i + 1);
        scanf("%d", &end);

        if (start > end)
        {
            printf("Invalid interval.\n");
            printf("Start must be less than or equal to end.\n");
            return 0;
        }

        /*
            Create start event.
        */

        events[2 * i].point = start;
        events[2 * i].type = 1;

        /*
            Create end event.
        */

        events[2 * i + 1].point = end;
        events[2 * i + 1].type = -1;
    }

    /*
        Sort all events.
    */

    mergeSort(events, 0, 2 * n - 1);

    /*
        Display sorted events.
    */

    printf("\n========================================\n");
    printf("          SORTED EVENTS\n");
    printf("========================================\n");

    for (int i = 0; i < 2 * n; i++)
    {
        if (events[i].type == 1)
        {
            printf("Point %d : Start\n",
                   events[i].point);
        }
        else
        {
            printf("Point %d : End\n",
                   events[i].point);
        }
    }

    /*
        Sweep through the events.
    */

    int current = 0;
    int maximum = 0;
    int bestPoint = events[0].point;

    printf("\n========================================\n");
    printf("             ANALYSIS\n");
    printf("========================================\n");

    for (int i = 0; i < 2 * n; i++)
    {
        /*
            Start event.
        */

        if (events[i].type == 1)
        {
            current++;

            printf("\nPoint %d:\n",
                   events[i].point);

            printf("  Interval starts\n");
            printf("  Intervals currently covering point = %d\n",
                   current);
        }

        /*
            End event.
        */

        else
        {
            printf("\nPoint %d:\n",
                   events[i].point);

            printf("  Interval ends\n");
            printf("  Intervals currently covering point = %d\n",
                   current);

            current--;
        }

        /*
            Update maximum.

            We check BEFORE decreasing current for an end
            because the endpoint itself belongs to the interval.
        */

        if (current > maximum)
        {
            maximum = current;
            bestPoint = events[i].point;
        }
    }

    /*
        Result.
    */

    printf("\n========================================\n");
    printf("              RESULT\n");
    printf("========================================\n");

    printf("Point with maximum coverage = %d\n",
           bestPoint);

    printf("Maximum number of intervals = %d\n",
           maximum);

    /*
        Complexity analysis.
    */

    printf("\n========================================\n");
    printf("          COMPLEXITY ANALYSIS\n");
    printf("========================================\n");

    printf("Number of events = 2n = O(n)\n");
    printf("Sorting events   = O(n log n)\n");
    printf("Scanning events  = O(n)\n");
    printf("Overall          = O(n log n)\n");

    return 0;
}