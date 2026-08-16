/*
 * DAA Lab-03, Q2: Search the Defective Coin
 *
 * There are n coins, all of identical required weight, except possibly
 * one coin which may be lighter than the rest (defective), or none may
 * be defective. Using a balance weighing scale (comparison of the sum
 * of weights of two groups), design a divide and conquer algorithm to
 * find the lighter coin, if it exists, in O(log2 n) weighings.
 *
 * Assumption: n is a power of 2 (standard simplification for this problem).
 * A weighing compares the total weight of the left half vs the right half.
 * If equal, both halves are genuine -> no defective coin exists.
 * If unequal, the lighter half contains the defective coin, so we recurse
 * into that half. This halves the search space each time -> log2(n) + c
 * weighings.
 */

#include <stdio.h>
#include <math.h>

int weighings = 0;

/* returns sum of weights of arr[lo..hi] */
int sumWeights(int arr[], int lo, int hi) {
    int s = 0;
    for (int i = lo; i <= hi; i++) s += arr[i];
    return s;
}

/* standardWeight = the known genuine per-coin weight (learned from a
 * balanced/heavier group during recursion) used to test the final
 * single remaining coin */
int findDefective(int arr[], int lo, int hi, int standardWeight) {
    if (lo == hi) {
        weighings++; /* compare the single coin against the standard weight */
        return (arr[lo] < standardWeight) ? lo : -1;
    }

    int mid = lo + (hi - lo) / 2;
    int leftCount = mid - lo + 1;
    int rightCount = hi - mid;

    int leftSum = sumWeights(arr, lo, mid);
    int rightSum = sumWeights(arr, mid + 1, hi);
    weighings++; /* one weighing: leftSum vs rightSum */

    if (leftSum == rightSum) {
        return -1; /* both halves genuine, no defect present */
    } else if (leftSum < rightSum) {
        /* right half is genuine -> its per-coin weight is the standard */
        return findDefective(arr, lo, mid, rightSum / rightCount);
    } else {
        return findDefective(arr, mid + 1, hi, leftSum / leftCount);
    }
}

int main() {
    int n;
    printf("Enter number of coins (power of 2): ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d coin weights (standard weight = 10, defective = 9):\n", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    /* initial standard weight: since at most one coin is defective (lighter),
       the maximum weight present in the array is guaranteed to be genuine */
    int standardWeight = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > standardWeight) standardWeight = arr[i];

    int idx = findDefective(arr, 0, n - 1, standardWeight);

    if (idx == -1)
        printf("\nNo defective coin found. All coins are genuine.\n");
    else
        printf("\nDefective (lighter) coin found at index %d (weight = %d).\n", idx, arr[idx]);

    printf("Number of weighings used: %d (approx log2(%d) = %.2f)\n",
           weighings, n, log2((double)n));

    return 0;
}