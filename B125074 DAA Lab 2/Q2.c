/*
 * ================================================================
 * DAA LAB-02 - QUESTION 2   (SVG version - no external libraries)
 *
 * Standard Merge Sort vs Modified 3-Way Merge Sort
 *
 * Requirement:
 *   Divide the input array into thirds instead of halves,
 *   recursively sort each third, and combine them using a
 *   three-way merge.
 *
 * This program:
 *   1. Implements standard 2-way merge sort.
 *   2. Implements modified 3-way merge sort.
 *   3. Uses the SAME input for both algorithms.
 *   4. Measures average running time.
 *   5. Verifies that both outputs are sorted.
 *   6. Prints theoretical complexity.
 *   7. Generates q2_mergesort_graph.svg
 *
 * Input sizes:
 *   20,000
 *   40,000
 *   ...
 *   200,000
 *
 * Compile:
 *   gcc q2_mergesort.c -o q2_mergesort -O2
 *
 * Run:
 *   ./q2_mergesort
 * ================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* ---------------------------------------------------------------
 * Configuration
 * --------------------------------------------------------------- */

#define NPTS 10

#define START_N 20000
#define STEP_N  20000

/*
 * Number of timing repetitions.
 *
 * Each repetition sorts a fresh copy of the same input.
 * Averaging makes the measurements more stable.
 */
#define RUNS 5

/* ---------------------------------------------------------------
 * SVG graph configuration
 * --------------------------------------------------------------- */

#define GRAPH_WIDTH   1100
#define GRAPH_HEIGHT  700

#define LEFT_MARGIN   110
#define RIGHT_MARGIN  230
#define TOP_MARGIN    80
#define BOTTOM_MARGIN 90

/* ===============================================================
 * TIMING
 * =============================================================== */

static double now_ms(void)
{
    return (double)clock() * 1000.0 / CLOCKS_PER_SEC;
}

/* ===============================================================
 * MEMORY ERROR
 * =============================================================== */

static void *checked_malloc(size_t size)
{
    void *p = malloc(size);

    if (p == NULL) {
        fprintf(stderr,
                "Memory allocation failed for %zu bytes.\n",
                size);
        exit(EXIT_FAILURE);
    }

    return p;
}

/* ===============================================================
 * STANDARD 2-WAY MERGE
 * =============================================================== */

static void merge2(
    int *a,
    int left,
    int mid,
    int right
)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = checked_malloc((size_t)n1 * sizeof(int));
    int *R = checked_malloc((size_t)n2 * sizeof(int));

    /* Copy left half. */
    for (int i = 0; i < n1; i++)
        L[i] = a[left + i];

    /* Copy right half. */
    for (int j = 0; j < n2; j++)
        R[j] = a[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    /* Merge the two sorted halves. */
    while (i < n1 && j < n2) {

        if (L[i] <= R[j])
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }

    /* Copy remaining left elements. */
    while (i < n1)
        a[k++] = L[i++];

    /* Copy remaining right elements. */
    while (j < n2)
        a[k++] = R[j++];

    free(L);
    free(R);
}

/* ===============================================================
 * STANDARD 2-WAY MERGE SORT
 * =============================================================== */

static void merge_sort_2way(
    int *a,
    int left,
    int right
)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    merge_sort_2way(a, left, mid);
    merge_sort_2way(a, mid + 1, right);

    merge2(a, left, mid, right);
}

/* ===============================================================
 * THREE-WAY MERGE
 * =============================================================== */

/*
 * Merge three already-sorted portions:
 *
 * A = [left ... m1]
 * B = [m1+1 ... m2]
 * C = [m2+1 ... right]
 *
 * At every step, the smallest current element among A, B and C
 * is selected.
 *
 * Running time = O(n).
 */

static void merge3(
    int *a,
    int left,
    int m1,
    int m2,
    int right
)
{
    int n1 = m1 - left + 1;
    int n2 = m2 - m1;
    int n3 = right - m2;

    int *A = checked_malloc((size_t)n1 * sizeof(int));
    int *B = checked_malloc((size_t)n2 * sizeof(int));
    int *C = checked_malloc((size_t)n3 * sizeof(int));

    /* Copy first part. */
    for (int i = 0; i < n1; i++)
        A[i] = a[left + i];

    /* Copy second part. */
    for (int i = 0; i < n2; i++)
        B[i] = a[m1 + 1 + i];

    /* Copy third part. */
    for (int i = 0; i < n3; i++)
        C[i] = a[m2 + 1 + i];

    int i = 0;
    int j = 0;
    int k = 0;

    int pos = left;

    /*
     * All three parts currently have elements.
     */
    while (i < n1 && j < n2 && k < n3) {

        if (A[i] <= B[j] && A[i] <= C[k]) {

            a[pos++] = A[i++];

        } else if (B[j] <= A[i] && B[j] <= C[k]) {

            a[pos++] = B[j++];

        } else {

            a[pos++] = C[k++];
        }
    }

    /*
     * At least one of the three arrays is now empty.
     *
     * Merge whichever two remain.
     */

    while (i < n1 && j < n2) {

        if (A[i] <= B[j])
            a[pos++] = A[i++];
        else
            a[pos++] = B[j++];
    }

    while (j < n2 && k < n3) {

        if (B[j] <= C[k])
            a[pos++] = B[j++];
        else
            a[pos++] = C[k++];
    }

    while (i < n1 && k < n3) {

        if (A[i] <= C[k])
            a[pos++] = A[i++];
        else
            a[pos++] = C[k++];
    }

    /* Copy anything left in A. */
    while (i < n1)
        a[pos++] = A[i++];

    /* Copy anything left in B. */
    while (j < n2)
        a[pos++] = B[j++];

    /* Copy anything left in C. */
    while (k < n3)
        a[pos++] = C[k++];

    free(A);
    free(B);
    free(C);
}

/* ===============================================================
 * MODIFIED 3-WAY MERGE SORT
 * =============================================================== */

static void merge_sort_3way(
    int *a,
    int left,
    int right
)
{
    /*
     * One element is already sorted.
     */
    if (left >= right)
        return;

    int n = right - left + 1;

    /*
     * Two elements.
     *
     * This also prevents invalid 3-way partitioning for n = 2.
     */
    if (n == 2) {

        if (a[left] > a[right]) {

            int temp = a[left];
            a[left] = a[right];
            a[right] = temp;
        }

        return;
    }

    /*
     * Divide into three approximately equal parts.
     *
     * The final part receives any remainder.
     */
    int third = n / 3;

    int m1 = left + third - 1;
    int m2 = left + 2 * third - 1;

    /*
     * For n >= 3, third is always >= 1.
     */
    merge_sort_3way(a, left, m1);

    merge_sort_3way(a, m1 + 1, m2);

    merge_sort_3way(a, m2 + 1, right);

    /*
     * Merge the three sorted parts.
     */
    merge3(a, left, m1, m2, right);
}

/* ===============================================================
 * CHECK SORTED
 * =============================================================== */

static int is_sorted(
    const int *a,
    int n
)
{
    for (int i = 1; i < n; i++) {

        if (a[i - 1] > a[i])
            return 0;
    }

    return 1;
}

/* ===============================================================
 * GENERATE INPUT
 * =============================================================== */

static void generate_input(
    int *a,
    int n
)
{
    /*
     * rand() gives a sufficiently random input for this lab.
     *
     * Using the same generated array for both algorithms makes
     * the comparison fair.
     */
    for (int i = 0; i < n; i++)
        a[i] = rand();
}

/* ===============================================================
 * BENCHMARK 2-WAY
 * =============================================================== */

static double benchmark_2way(
    const int *input,
    int n
)
{
    double total = 0.0;

    for (int run = 0; run < RUNS; run++) {

        int *a =
            checked_malloc((size_t)n * sizeof(int));

        memcpy(
            a,
            input,
            (size_t)n * sizeof(int)
        );

        double start = now_ms();

        merge_sort_2way(
            a,
            0,
            n - 1
        );

        double end = now_ms();

        total += end - start;

        /*
         * Make sure the compiler cannot treat the sort as
         * irrelevant.
         */
        if (!is_sorted(a, n)) {

            fprintf(
                stderr,
                "ERROR: 2-way merge sort failed for n=%d\n",
                n
            );

            free(a);
            exit(EXIT_FAILURE);
        }

        free(a);
    }

    return total / RUNS;
}

/* ===============================================================
 * BENCHMARK 3-WAY
 * =============================================================== */

static double benchmark_3way(
    const int *input,
    int n
)
{
    double total = 0.0;

    for (int run = 0; run < RUNS; run++) {

        int *a =
            checked_malloc((size_t)n * sizeof(int));

        memcpy(
            a,
            input,
            (size_t)n * sizeof(int)
        );

        double start = now_ms();

        merge_sort_3way(
            a,
            0,
            n - 1
        );

        double end = now_ms();

        total += end - start;

        /*
         * Validate the result.
         */
        if (!is_sorted(a, n)) {

            fprintf(
                stderr,
                "ERROR: 3-way merge sort failed for n=%d\n",
                n
            );

            free(a);
            exit(EXIT_FAILURE);
        }

        free(a);
    }

    return total / RUNS;
}

/* ===============================================================
 * SVG GRAPH GENERATION
 * =============================================================== */

static void svg_escape(FILE *fp, const char *text)
{
    while (*text) {

        switch (*text) {

            case '&':
                fprintf(fp, "&amp;");
                break;

            case '<':
                fprintf(fp, "&lt;");
                break;

            case '>':
                fprintf(fp, "&gt;");
                break;

            case '"':
                fprintf(fp, "&quot;");
                break;

            default:
                fputc(*text, fp);
        }

        text++;
    }
}

static void generate_svg_graph(
    const char *filename,
    const int sizes[NPTS],
    const double time2[NPTS],
    const double time3[NPTS]
)
{
    FILE *fp = fopen(filename, "w");

    if (fp == NULL) {
        fprintf(stderr, "Could not create %s\n", filename);
        return;
    }

    const int plot_left = LEFT_MARGIN;
    const int plot_right = GRAPH_WIDTH - RIGHT_MARGIN;
    const int plot_top = TOP_MARGIN;
    const int plot_bottom = GRAPH_HEIGHT - BOTTOM_MARGIN;

    const double plot_width = plot_right - plot_left;
    const double plot_height = plot_bottom - plot_top;

    double max_value = 0.0;

    for (int p = 0; p < NPTS; p++) {

        if (time2[p] > max_value)
            max_value = time2[p];

        if (time3[p] > max_value)
            max_value = time3[p];
    }

    if (max_value <= 0.0)
        max_value = 1.0;

    max_value *= 1.10;

    fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");

    fprintf(fp,
        "<svg xmlns=\"http://www.w3.org/2000/svg\" "
        "width=\"%d\" height=\"%d\" viewBox=\"0 0 %d %d\">\n",
        GRAPH_WIDTH, GRAPH_HEIGHT, GRAPH_WIDTH, GRAPH_HEIGHT
    );

    fprintf(fp,
        "<rect x=\"0\" y=\"0\" width=\"%d\" height=\"%d\" "
        "fill=\"white\"/>\n",
        GRAPH_WIDTH, GRAPH_HEIGHT
    );

    /* Title */
    fprintf(fp,
        "<text x=\"%d\" y=\"40\" font-family=\"Arial\" "
        "font-size=\"24\" font-weight=\"bold\" "
        "text-anchor=\"middle\">"
        "Merge Sort: 2-Way vs 3-Way</text>\n",
        GRAPH_WIDTH / 2
    );

    /* Horizontal grid + Y labels (milliseconds) */
    for (int i = 0; i <= 5; i++) {

        double fraction = (double)i / 5.0;
        double y = plot_bottom - fraction * plot_height;

        fprintf(fp,
            "<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" "
            "stroke=\"#dddddd\" stroke-width=\"1\"/>\n",
            (double)plot_left, y, (double)plot_right, y
        );

        double label = fraction * max_value;

        fprintf(fp,
            "<text x=\"%d\" y=\"%.2f\" font-family=\"Arial\" "
            "font-size=\"12\" text-anchor=\"end\">%.4g</text>\n",
            plot_left - 10, y + 4, label
        );
    }

    /* X ticks + labels (input size n) */
    for (int p = 0; p < NPTS; p++) {

        double fraction = (double)p / (NPTS - 1);
        double x = plot_left + fraction * plot_width;

        fprintf(fp,
            "<line x1=\"%.2f\" y1=\"%d\" x2=\"%.2f\" y2=\"%d\" "
            "stroke=\"#dddddd\" stroke-width=\"1\"/>\n",
            x, plot_top, x, plot_bottom
        );

        fprintf(fp,
            "<text x=\"%.2f\" y=\"%d\" font-family=\"Arial\" "
            "font-size=\"11\" text-anchor=\"middle\">%d</text>\n",
            x, plot_bottom + 22, sizes[p]
        );
    }

    /* Axes */
    fprintf(fp,
        "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" "
        "stroke=\"black\" stroke-width=\"2\"/>\n",
        plot_left, plot_bottom, plot_right, plot_bottom
    );

    fprintf(fp,
        "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" "
        "stroke=\"black\" stroke-width=\"2\"/>\n",
        plot_left, plot_bottom, plot_left, plot_top
    );

    /* Axis labels */
    fprintf(fp,
        "<text x=\"%d\" y=\"%d\" font-family=\"Arial\" "
        "font-size=\"16\" font-weight=\"bold\" "
        "text-anchor=\"middle\">Input Size (n)</text>\n",
        (plot_left + plot_right) / 2, GRAPH_HEIGHT - 25
    );

    fprintf(fp,
        "<text x=\"25\" y=\"%d\" font-family=\"Arial\" "
        "font-size=\"16\" font-weight=\"bold\" "
        "transform=\"rotate(-90 25 %d)\" "
        "text-anchor=\"middle\">Average Time (ms)</text>\n",
        (plot_top + plot_bottom) / 2, (plot_top + plot_bottom) / 2
    );

    /* Curve drawing helper (inline, twice: red=2-way, blue=3-way) */
    const double *series[2] = { time2, time3 };
    const char *colors[2] = { "#e41a1c", "#377eb8" };

    for (int s = 0; s < 2; s++) {

        fprintf(fp,
            "<polyline fill=\"none\" stroke=\"%s\" "
            "stroke-width=\"3\" points=\"",
            colors[s]
        );

        for (int p = 0; p < NPTS; p++) {

            double fraction = (double)p / (NPTS - 1);
            double x = plot_left + fraction * plot_width;
            double y = plot_bottom -
                       (series[s][p] / max_value) * plot_height;

            fprintf(fp, "%.2f,%.2f ", x, y);
        }

        fprintf(fp, "\"/>\n");

        for (int p = 0; p < NPTS; p++) {

            double fraction = (double)p / (NPTS - 1);
            double x = plot_left + fraction * plot_width;
            double y = plot_bottom -
                       (series[s][p] / max_value) * plot_height;

            fprintf(fp,
                "<circle cx=\"%.2f\" cy=\"%.2f\" r=\"4\" "
                "fill=\"%s\"/>\n",
                x, y, colors[s]
            );
        }
    }

    /* Legend */
    int legend_x = plot_right + 20;
    int legend_y = plot_top + 20;

    fprintf(fp,
        "<text x=\"%d\" y=\"%d\" font-family=\"Arial\" "
        "font-size=\"15\" font-weight=\"bold\">Algorithm</text>\n",
        legend_x, legend_y
    );

    const char *labels[2] = {
        "2-Way Merge Sort",
        "3-Way Merge Sort"
    };

    for (int s = 0; s < 2; s++) {

        int y = legend_y + 30 + s * 30;

        fprintf(fp,
            "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" "
            "stroke=\"%s\" stroke-width=\"4\"/>\n",
            legend_x, y, legend_x + 25, y, colors[s]
        );

        fprintf(fp,
            "<text x=\"%d\" y=\"%d\" font-family=\"Arial\" "
            "font-size=\"12\">",
            legend_x + 35, y + 4
        );

        svg_escape(fp, labels[s]);

        fprintf(fp, "</text>\n");
    }

    fprintf(fp, "</svg>\n");

    fclose(fp);
}

/* ===============================================================
 * MAIN
 * =============================================================== */

int main(void)
{
    /*
     * Fixed seed makes the experiment reproducible.
     */
    srand(12345);

    int sizes[NPTS];
    double time2[NPTS];
    double time3[NPTS];

    printf("\n");
    printf("=================================================================\n");
    printf("       DAA LAB-02 - QUESTION 2\n");
    printf("       Standard Merge Sort vs 3-Way Merge Sort\n");
    printf("=================================================================\n");

    printf("\n");
    printf("Each timing is the average of %d runs.\n", RUNS);
    printf("The same input is used for both algorithms.\n");

    printf("\n");
    printf(
        "%-12s %-20s %-20s %-15s\n",
        "n", "2-Way (ms)", "3-Way (ms)", "Validation"
    );

    printf(
        "-----------------------------------------------------------------\n"
    );

    for (int p = 0; p < NPTS; p++) {

        int n = START_N + p * STEP_N;

        sizes[p] = n;

        int *input = checked_malloc((size_t)n * sizeof(int));

        generate_input(input, n);

        time2[p] = benchmark_2way(input, n);
        time3[p] = benchmark_3way(input, n);

        printf(
            "%-12d %-20.4f %-20.4f %-15s\n",
            n, time2[p], time3[p], "OK / OK"
        );

        free(input);
    }

    printf("\n");
    printf("=================================================================\n");
    printf("                     THEORETICAL ANALYSIS\n");
    printf("=================================================================\n");

    printf("\nStandard 2-Way Merge Sort:\n");
    printf("  Divide into 2 subarrays.\n");
    printf("  Merge costs O(n).\n");
    printf("  Recurrence: T(n) = 2T(n/2) + O(n)\n");
    printf("  Worst-case: T(n) = O(n log n)\n");

    printf("\nModified 3-Way Merge Sort:\n");
    printf("  Divide into 3 subarrays.\n");
    printf("  Three-way merge costs O(n).\n");
    printf("  Recurrence: T(n) = 3T(n/3) + O(n)\n");
    printf("  Worst-case: T(n) = O(n log n)\n");

    printf("\nConclusion:\n");
    printf("  Both standard merge sort and modified 3-way merge sort\n");
    printf("  have worst-case running time O(n log n).\n");

    printf("\n");
    printf("=================================================================\n");
    printf("                     GENERATING GRAPH\n");
    printf("=================================================================\n");

    generate_svg_graph(
        "q2_mergesort_graph.svg",
        sizes,
        time2,
        time3
    );

    printf("\nGraph saved as: q2_mergesort_graph.svg\n");

    printf("\n");
    printf("=================================================================\n");
    printf("                         Q2 COMPLETE\n");
    printf("=================================================================\n");

    printf("\n");

    return 0;
}