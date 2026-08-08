/*
 * ================================================================
 * DAA LAB-02 - QUESTION 3   (SVG version - no external libraries)
 *
 * Merging k Sorted Arrays
 *
 * METHOD 1:
 *   Sequential merging:
 *       (((A1 + A2) + A3) + ... + Ak)
 *
 * METHOD 2:
 *   Pairwise merging:
 *       (A1+A2), (A3+A4), ...
 *       then merge the results pairwise until one array remains.
 *
 * REQUIREMENT:
 *   k sorted arrays, each containing n elements.
 *
 * THEORETICAL COMPLEXITY:
 *   Method 1 = O(n * k^2)
 *   Method 2 = O(n * k * log k)
 *
 * EXPERIMENT:
 *   n is fixed.
 *   k = 2, 4, 8, 16, 32, 64, 128, 256
 *
 * OUTPUT:
 *   q3_kmerge_graph.svg
 *
 * COMPILE:
 *   gcc q3_kmerge.c -o q3_kmerge -O2
 *
 * RUN:
 *   ./q3_kmerge
 * ================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* ================================================================
 * CONFIGURATION
 * ================================================================ */

#define NPTS 8

/*
 * Fixed number of elements in EACH sorted array.
 */
#define N 1000

/*
 * Number of repetitions for timing.
 */
#define RUNS 5

/*
 * k values.
 *
 * Powers of two make the pairwise merging perfectly balanced.
 */
static const int K_VALUES[NPTS] = {
    2, 4, 8, 16, 32, 64, 128, 256
};

/* ================================================================
 * SVG graph configuration
 * ================================================================ */

#define GRAPH_WIDTH   1100
#define GRAPH_HEIGHT  700

#define LEFT_MARGIN   110
#define RIGHT_MARGIN  230
#define TOP_MARGIN    80
#define BOTTOM_MARGIN 90

/* ================================================================
 * TIMING
 * ================================================================ */

static double now_ms(void)
{
    return (double)clock() * 1000.0 / CLOCKS_PER_SEC;
}

/* ================================================================
 * SAFE MEMORY ALLOCATION
 * ================================================================ */

static void *checked_malloc(size_t size)
{
    void *ptr = malloc(size);

    if (ptr == NULL) {
        fprintf(
            stderr,
            "Memory allocation failed for %zu bytes.\n",
            size
        );
        exit(EXIT_FAILURE);
    }

    return ptr;
}

/* ================================================================
 * INTEGER COMPARISON
 * ================================================================ */

static int compare_ints(
    const void *a,
    const void *b
)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y)
        return -1;

    if (x > y)
        return 1;

    return 0;
}

/* ================================================================
 * MERGE TWO SORTED ARRAYS
 *
 * Time:
 *   O(na + nb)
 *
 * Space:
 *   O(na + nb)
 * ================================================================ */

static int *merge_two(
    const int *a,
    int na,
    const int *b,
    int nb
)
{
    int total = na + nb;

    int *out =
        checked_malloc(
            (size_t)total * sizeof(int)
        );

    int i = 0;
    int j = 0;
    int p = 0;

    while (i < na && j < nb) {

        if (a[i] <= b[j])
            out[p++] = a[i++];
        else
            out[p++] = b[j++];
    }

    while (i < na)
        out[p++] = a[i++];

    while (j < nb)
        out[p++] = b[j++];

    return out;
}

/* ================================================================
 * METHOD 1 - SEQUENTIAL MERGING
 *
 * (((A1+A2)+A3)+...+Ak)
 *
 * Merge costs:
 *
 *   2n + 3n + 4n + ... + kn
 *
 * = n(2 + 3 + ... + k)
 *
 * = O(nk^2)
 * ================================================================ */

static int *method1(
    int **arrays,
    int n,
    int k,
    int *result_length
)
{
    /*
     * Start with a copy of A1.
     */
    int *result =
        checked_malloc(
            (size_t)n * sizeof(int)
        );

    memcpy(
        result,
        arrays[0],
        (size_t)n * sizeof(int)
    );

    int current_length = n;

    /*
     * Merge A2, A3, ..., Ak one at a time.
     */
    for (int i = 1; i < k; i++) {

        int *merged =
            merge_two(
                result,
                current_length,
                arrays[i],
                n
            );

        free(result);

        result = merged;

        current_length += n;
    }

    *result_length = current_length;

    return result;
}

/* ================================================================
 * METHOD 2 - PAIRWISE MERGING
 *
 * Merge pairs at every level.
 *
 * Example for k = 8:
 *
 * Level 1:
 *   A1+A2
 *   A3+A4
 *   A5+A6
 *   A7+A8
 *
 * Level 2:
 *   (A1+A2)+(A3+A4)
 *   (A5+A6)+(A7+A8)
 *
 * Level 3:
 *   previous result + previous result
 *
 * Number of levels:
 *   log2(k)
 *
 * Work per level:
 *   O(nk)
 *
 * Total:
 *   O(nk log k)
 *
 * This implementation ALSO handles odd k safely.
 * ================================================================ */

static int *method2(
    int **arrays,
    int n,
    int k,
    int *result_length
)
{
    /*
     * Current arrays.
     *
     * We copy the original arrays so that the function owns
     * everything it manages.
     */
    int **current =
        checked_malloc(
            (size_t)k * sizeof(int *)
        );

    int *lengths =
        checked_malloc(
            (size_t)k * sizeof(int)
        );

    for (int i = 0; i < k; i++) {

        current[i] =
            checked_malloc(
                (size_t)n * sizeof(int)
            );

        memcpy(
            current[i],
            arrays[i],
            (size_t)n * sizeof(int)
        );

        lengths[i] = n;
    }

    int count = k;

    /*
     * Continue until exactly one array remains.
     */
    while (count > 1) {

        /*
         * If count is odd, the last array is carried forward
         * unchanged.
         *
         * Therefore:
         *
         *   new_count = ceil(count / 2)
         */
        int new_count =
            (count + 1) / 2;

        int **next =
            checked_malloc(
                (size_t)new_count * sizeof(int *)
            );

        int *new_lengths =
            checked_malloc(
                (size_t)new_count * sizeof(int)
            );

        int out = 0;

        /*
         * Merge adjacent pairs.
         */
        for (int i = 0; i + 1 < count; i += 2) {

            next[out] =
                merge_two(
                    current[i],
                    lengths[i],
                    current[i + 1],
                    lengths[i + 1]
                );

            new_lengths[out] =
                lengths[i] +
                lengths[i + 1];

            free(current[i]);
            free(current[i + 1]);

            out++;
        }

        /*
         * If count was odd, carry the final array forward.
         */
        if (count % 2 != 0) {

            next[out] = current[count - 1];

            new_lengths[out] =
                lengths[count - 1];

            out++;
        }

        free(current);
        free(lengths);

        current = next;
        lengths = new_lengths;
        count = new_count;
    }

    /*
     * Exactly one array remains.
     */
    int *result = current[0];

    *result_length = lengths[0];

    free(current);
    free(lengths);

    return result;
}

/* ================================================================
 * CHECK SORTED
 * ================================================================ */

static int is_sorted(
    const int *a,
    int n
)
{
    if (a == NULL || n < 0)
        return 0;

    for (int i = 1; i < n; i++) {

        if (a[i - 1] > a[i])
            return 0;
    }

    return 1;
}

/* ================================================================
 * CHECK TWO ARRAYS ARE IDENTICAL
 * ================================================================ */

static int arrays_equal(
    const int *a,
    const int *b,
    int n
)
{
    if (a == NULL || b == NULL || n < 0)
        return 0;

    for (int i = 0; i < n; i++) {

        if (a[i] != b[i])
            return 0;
    }

    return 1;
}

/* ================================================================
 * CREATE k SORTED ARRAYS
 *
 * Each array contains exactly n elements.
 * ================================================================ */

static int **create_sorted_arrays(
    int n,
    int k
)
{
    int **arrays =
        checked_malloc(
            (size_t)k * sizeof(int *)
        );

    for (int i = 0; i < k; i++) {

        arrays[i] =
            checked_malloc(
                (size_t)n * sizeof(int)
            );

        /*
         * Generate random integers.
         */
        for (int j = 0; j < n; j++)
            arrays[i][j] =
                rand() % 1000000;

        /*
         * Sort this individual array.
         *
         * Sorting is NOT included in the merge timing.
         */
        qsort(
            arrays[i],
            (size_t)n,
            sizeof(int),
            compare_ints
        );
    }

    return arrays;
}

/* ================================================================
 * FREE k ARRAYS
 * ================================================================ */

static void free_arrays(
    int **arrays,
    int k
)
{
    if (arrays == NULL)
        return;

    for (int i = 0; i < k; i++)
        free(arrays[i]);

    free(arrays);
}

/* ================================================================
 * BENCHMARK METHOD 1
 *
 * The arrays are already sorted.
 *
 * Only the merging is timed.
 * ================================================================ */

static double benchmark_method1(
    int **arrays,
    int n,
    int k
)
{
    double total = 0.0;

    for (int run = 0; run < RUNS; run++) {

        int result_length = 0;

        double start = now_ms();

        int *result =
            method1(
                arrays,
                n,
                k,
                &result_length
            );

        double end = now_ms();

        /*
         * Validate while the result is still available.
         */
        int expected_length = n * k;

        if (result_length != expected_length ||
            !is_sorted(result, result_length)) {

            fprintf(
                stderr,
                "ERROR: Method 1 produced an invalid result "
                "for k=%d.\n",
                k
            );

            free(result);
            exit(EXIT_FAILURE);
        }

        total += end - start;

        free(result);
    }

    return total / RUNS;
}

/* ================================================================
 * BENCHMARK METHOD 2
 * ================================================================ */

static double benchmark_method2(
    int **arrays,
    int n,
    int k
)
{
    double total = 0.0;

    for (int run = 0; run < RUNS; run++) {

        int result_length = 0;

        double start = now_ms();

        int *result =
            method2(
                arrays,
                n,
                k,
                &result_length
            );

        double end = now_ms();

        int expected_length = n * k;

        if (result_length != expected_length ||
            !is_sorted(result, result_length)) {

            fprintf(
                stderr,
                "ERROR: Method 2 produced an invalid result "
                "for k=%d.\n",
                k
            );

            free(result);
            exit(EXIT_FAILURE);
        }

        total += end - start;

        free(result);
    }

    return total / RUNS;
}

/* ================================================================
 * SVG GRAPH GENERATION
 * ================================================================ */

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
    const int k_values[NPTS],
    const double method1_times[NPTS],
    const double method2_times[NPTS]
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

        if (method1_times[p] > max_value)
            max_value = method1_times[p];

        if (method2_times[p] > max_value)
            max_value = method2_times[p];
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
        "Merging k Sorted Arrays: Sequential vs Pairwise</text>\n",
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

    /* X ticks + labels (k values) - NOT evenly spaced numerically,
     * but evenly spaced on the axis (categorical), since k doubles
     * each time. This matches how the data was collected. */
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
            "font-size=\"12\" text-anchor=\"middle\">k=%d</text>\n",
            x, plot_bottom + 22, k_values[p]
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
        "text-anchor=\"middle\">Number of Arrays (k)</text>\n",
        (plot_left + plot_right) / 2, GRAPH_HEIGHT - 25
    );

    fprintf(fp,
        "<text x=\"25\" y=\"%d\" font-family=\"Arial\" "
        "font-size=\"16\" font-weight=\"bold\" "
        "transform=\"rotate(-90 25 %d)\" "
        "text-anchor=\"middle\">Average Time (ms)</text>\n",
        (plot_top + plot_bottom) / 2, (plot_top + plot_bottom) / 2
    );

    /* Curves: red=Method1 (sequential), blue=Method2 (pairwise) */
    const double *series[2] = { method1_times, method2_times };
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
        "font-size=\"15\" font-weight=\"bold\">Method</text>\n",
        legend_x, legend_y
    );

    const char *labels[2] = {
        "Method 1: Sequential",
        "Method 2: Pairwise"
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

    /*
     * k_values is deliberately used here to document that the
     * graph corresponds to these exact experimental points.
     */
    (void)k_values;
}

/* ================================================================
 * MAIN
 * ================================================================ */

int main(void)
{
    /*
     * Fixed seed gives reproducible input generation.
     */
    srand(12345);

    double method1_times[NPTS];
    double method2_times[NPTS];
    int sizes_out[NPTS];

    printf("\n");
    printf("===============================================================\n");
    printf("              DAA LAB-02 - QUESTION 3\n");
    printf("              Merging k Sorted Arrays\n");
    printf("===============================================================\n");

    printf("\n");
    printf("Each sorted array contains n = %d elements.\n", N);

    printf(
        "Each timing is the average of %d runs.\n",
        RUNS
    );

    printf(
        "Input generation and individual-array sorting are NOT timed.\n"
    );

    printf("\n");

    printf(
        "%-10s %-20s %-20s %-30s\n",
        "k",
        "Method 1 (ms)",
        "Method 2 (ms)",
        "Validation"
    );

    printf(
        "--------------------------------------------------------------------------\n"
    );

    for (int p = 0; p < NPTS; p++) {

        int k = K_VALUES[p];

        sizes_out[p] = k;

        /*
         * Create the SAME set of sorted arrays for both methods.
         */
        int **arrays =
            create_sorted_arrays(
                N,
                k
            );

        method1_times[p] =
            benchmark_method1(
                arrays,
                N,
                k
            );

        method2_times[p] =
            benchmark_method2(
                arrays,
                N,
                k
            );

        /*
         * Run both methods once more for direct comparison.
         *
         * This does NOT contribute to the timing measurements.
         * It is solely for validating that both produce exactly
         * the same sorted result.
         */
        int length1 = 0;
        int length2 = 0;

        int *result1 =
            method1(
                arrays,
                N,
                k,
                &length1
            );

        int *result2 =
            method2(
                arrays,
                N,
                k,
                &length2
            );

        int expected_length =
            N * k;

        int valid =
            length1 == expected_length &&
            length2 == expected_length &&
            is_sorted(result1, length1) &&
            is_sorted(result2, length2) &&
            arrays_equal(
                result1,
                result2,
                expected_length
            );

        printf(
            "%-10d %-20.4f %-20.4f %-30s\n",
            k,
            method1_times[p],
            method2_times[p],
            valid ? "PASS" : "FAIL"
        );

        if (!valid) {

            fprintf(
                stderr,
                "\nERROR: Validation failed for k=%d.\n",
                k
            );

            free(result1);
            free(result2);
            free_arrays(arrays, k);

            return EXIT_FAILURE;
        }

        free(result1);
        free(result2);

        free_arrays(
            arrays,
            k
        );
    }

    printf("\n");
    printf("===============================================================\n");
    printf("                    THEORETICAL ANALYSIS\n");
    printf("===============================================================\n");

    printf("\nMethod 1: Sequential merging\n");
    printf("  First merge:       2n elements\n");
    printf("  Second merge:      3n elements\n");
    printf("  Third merge:       4n elements\n");
    printf("  ...\n");
    printf("  Final merge:       kn elements\n");
    printf("\n");
    printf("  T(n,k) = 2n + 3n + 4n + ... + kn\n");
    printf("  T(n,k) = n(2 + 3 + ... + k)\n");
    printf("  T(n,k) = O(n*k^2)\n");

    printf("\nMethod 2: Pairwise merging\n");
    printf("  At each level, all k*n elements are processed.\n");
    printf("  Number of levels = log2(k)\n");
    printf("  T(n,k) = O(n*k*log(k))\n");

    printf("\nTherefore:\n");
    printf("  Method 1 = O(n*k^2)\n");
    printf("  Method 2 = O(n*k*log(k))\n");

    printf("\nExperimental setup:\n");
    printf("  n is fixed at %d.\n", N);
    printf("  k varies as 2, 4, 8, 16, 32, 64, 128, 256.\n");
    printf("  Therefore the graph shows growth with respect to k.\n");

    printf("\n");
    printf("===============================================================\n");
    printf("                     GENERATING GRAPH\n");
    printf("===============================================================\n");

    generate_svg_graph(
        "q3_kmerge_graph.svg",
        sizes_out,
        method1_times,
        method2_times
    );

    printf("\n");
    printf(
        "Graph saved as: q3_kmerge_graph.svg\n"
    );

    printf("\nLegend:\n");
    printf("  RED  = Method 1: Sequential Merge\n");
    printf("  BLUE = Method 2: Pairwise Merge\n");

    printf("\n");
    printf(
        "All validation tests passed.\n"
    );

    printf(
        "Q3 completed successfully.\n"
    );

    printf(
        "\n===============================================================\n"
    );

    return EXIT_SUCCESS;
}