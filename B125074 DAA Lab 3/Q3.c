/*
 * DAA Lab-03, Q3: Max and Min using D&C Approach
 *
 * Using the divide and conquer approach, find the maximum and minimum
 * elements in an array of size n so that the number of comparisons is
 * bounded by 3n/2. Implement and validate with a comparison counter.
 */

#include <stdio.h>

int comparisons = 0;

typedef struct {
    int max, min;
} Pair;

Pair maxMin(int arr[], int lo, int hi) {
    Pair result;

    /* base case: only one element */
    if (lo == hi) {
        result.max = result.min = arr[lo];
        return result;
    }

    /* base case: two elements -> 1 comparison */
    if (hi - lo == 1) {
        comparisons++;
        if (arr[lo] < arr[hi]) {
            result.min = arr[lo];
            result.max = arr[hi];
        } else {
            result.min = arr[hi];
            result.max = arr[lo];
        }
        return result;
    }

    /* divide */
    int mid = lo + (hi - lo) / 2;
    Pair left = maxMin(arr, lo, mid);
    Pair right = maxMin(arr, mid + 1, hi);

    /* combine: 2 comparisons */
    comparisons++;
    result.max = (left.max > right.max) ? left.max : right.max;
    comparisons++;
    result.min = (left.min < right.min) ? left.min : right.min;

    return result;
}

int main() {
    int n;
    printf("Enter size of array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    Pair res = maxMin(arr, 0, n - 1);

    printf("\nMaximum = %d\n", res.max);
    printf("Minimum = %d\n", res.min);
    printf("Comparisons used = %d (bound: 3n/2 = %.1f)\n", comparisons, 3.0 * n / 2);

    return 0;
}