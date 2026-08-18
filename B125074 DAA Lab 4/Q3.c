// Application of sorting-III: Given a set S of n integers and an integer T, give an O(nk−1· log n) algorithm to test whether k of the integers in S add up to T. By choosing the proper input representation, write a program in C to validate your algorithm.

/* ALGORITHM FindKSum(S, n, T, k)

    Sort S in ascending order

    IF k = 2 THEN
        RETURN FindPair(S, n, T)

    FOR i ← 1 TO n DO

        target ← T - S[i]

        IF FindKSum(S after i, n - i, target, k - 1)
           = TRUE THEN

            OUTPUT "k-sum found"
            RETURN TRUE

    END FOR

    RETURN FALSE

END ALGORITHM */

#include <stdio.h>

/* ---------------------------------------------------------
   Merge two sorted parts
   --------------------------------------------------------- */

void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
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

void mergeSort(int arr[], int left, int right)
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
   Binary Search
   --------------------------------------------------------- */

int binarySearch(int arr[], int left, int right, int target)
{
    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
            return mid;

        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

/* ---------------------------------------------------------
   K-Sum
   --------------------------------------------------------- */

int findKSum(int S[],
            int start,
            int n,
            int k,
            int target,
            int solution[],
            int position)
{
    /*
        Base case:
        Find 2 elements whose sum is target.
    */

    if (k == 2)
    {
        int found = 0;

        for (int i = start; i < n - 1; i++)
        {
            /*
                Skip duplicate starting values.
            */
            if (i > start && S[i] == S[i - 1])
                continue;

            int required = target - S[i];

            /*
                Search only after i.
                This prevents using the same element twice.
            */

            if (binarySearch(S, i + 1, n - 1, required) != -1)
            {
                solution[position] = S[i];
                solution[position + 1] = required;

                printf("(");

                for (int j = 0; j < position + 2; j++)
                {
                    printf("%d", solution[j]);

                    if (j < position + 1)
                        printf(", ");
                }

                printf(")\n");

                found = 1;
            }
        }

        return found;
    }

    /*
        Recursive case.

        Choose one element and find the remaining
        k - 1 elements.
    */

    int found = 0;

    for (int i = start; i <= n - k; i++)
    {
        /*
            Skip duplicate values at this level.

            Example:
                3 3 4 4 6

            We don't want to generate the same
            combination multiple times.
        */

        if (i > start && S[i] == S[i - 1])
            continue;

        solution[position] = S[i];

        int remainingTarget = target - S[i];

        /*
            Recursively find k - 1 elements.
        */

        if (findKSum(S,
                     i + 1,
                     n,
                     k - 1,
                     remainingTarget,
                     solution,
                     position + 1))
        {
            found = 1;
        }
    }

    return found;
}

/* ---------------------------------------------------------
   Main
   --------------------------------------------------------- */

int main()
{
    int n, k, T;

    printf("========================================\n");
    printf("          K-SUM PROBLEM\n");
    printf("========================================\n");

    printf("\nEnter number of elements: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Number of elements must be positive.\n");
        return 0;
    }

    int S[n];

    printf("\nEnter %d elements:\n", n);

    for (int i = 0; i < n; i++)
    {
        printf("S[%d]: ", i + 1);
        scanf("%d", &S[i]);
    }

    printf("\nEnter value of k: ");
    scanf("%d", &k);

    printf("Enter target T: ");
    scanf("%d", &T);

    /*
        Validate k.
    */

    if (k < 2 || k > n)
    {
        printf("\nInvalid value of k.\n");
        printf("k must satisfy 2 <= k <= n.\n");
        return 0;
    }

    /*
        Sort the array.
    */

    mergeSort(S, 0, n - 1);

    printf("\n========================================\n");
    printf("          SORTED ARRAY\n");
    printf("========================================\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", S[i]);
    }

    printf("\n");

    /*
        Store the k elements found.
    */

    int solution[k];

    printf("\n========================================\n");
    printf("        SETS OF %d ELEMENTS\n", k);
    printf("========================================\n");

    int found = findKSum(S,
                          0,
                          n,
                          k,
                          T,
                          solution,
                          0);

    /*
        Result.
    */

    printf("\n========================================\n");
    printf("              RESULT\n");
    printf("========================================\n");

    if (found)
    {
        printf("At least one set of %d elements adds up to %d.\n",
               k, T);
    }
    else
    {
        printf("No set of %d elements adds up to %d.\n",
               k, T);
    }

    /*
        Complexity analysis.
    */

    printf("\n========================================\n");
    printf("          COMPLEXITY ANALYSIS\n");
    printf("========================================\n");

    printf("Merge Sort       = O(n log n)\n");
    printf("K-Sum search     = O(n^(k-1) log n)\n");
    printf("Overall          = O(n^(k-1) log n)\n");

    printf("\nReason:\n");
    printf("For k = 2, binary search takes O(log n)\n");
    printf("and it is performed for O(n) elements.\n");

    printf("For each additional element, the search\n");
    printf("branches over O(n) possibilities.\n");

    return 0;
}