/*
 * ================================================================
 * DAA LAB-02 - QUESTION 1
 * Dictionary Operations on Six Data Structures
 *
 * Operations:
 *   Search, Insert, Delete, Minimum, Maximum,
 *   Predecessor, Successor
 *
 * Data Structures:
 *   1. Unsorted Array
 *   2. Sorted Array
 *   3. Singly Linked Unsorted List
 *   4. Singly Linked Sorted List
 *   5. Doubly Linked Unsorted List
 *   6. Doubly Linked Sorted List
 *
 * The program:
 *   - prints theoretical worst-case complexities
 *   - performs experimental timing
 *   - prints measured timings
 *   - generates 7 SVG growth plots
 *
 * Compile:
 *   gcc q1_dictionary.c -o q1_dictionary -O2
 *
 * Run:
 *   ./q1_dictionary
 *
 * Generated graphs:
 *   q1_search_graph.svg
 *   q1_insert_graph.svg
 *   q1_delete_graph.svg
 *   q1_minimum_graph.svg
 *   q1_maximum_graph.svg
 *   q1_predecessor_graph.svg
 *   q1_successor_graph.svg
 * ================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <limits.h>

/* ---------------------------------------------------------------
 * Experiment configuration
 * --------------------------------------------------------------- */

#define START_N       1000
#define STEP_N        1000
#define NPTS          10

#define STRUCTS       6
#define OPS           7

#define MAX_VALUE     1000000000

#define GRAPH_WIDTH   1100
#define GRAPH_HEIGHT  700

#define LEFT_MARGIN   100
#define RIGHT_MARGIN  260
#define TOP_MARGIN    80
#define BOTTOM_MARGIN 90

/* ---------------------------------------------------------------
 * Names
 * --------------------------------------------------------------- */

const char *structure_names[STRUCTS] = {
    "Unsorted Array",
    "Sorted Array",
    "SLL Unsorted",
    "SLL Sorted",
    "DLL Unsorted",
    "DLL Sorted"
};

const char *operation_names[OPS] = {
    "Search",
    "Insert",
    "Delete",
    "Minimum",
    "Maximum",
    "Predecessor",
    "Successor"
};

const char *graph_files[OPS] = {
    "q1_search_graph.svg",
    "q1_insert_graph.svg",
    "q1_delete_graph.svg",
    "q1_minimum_graph.svg",
    "q1_maximum_graph.svg",
    "q1_predecessor_graph.svg",
    "q1_successor_graph.svg"
};

/* ---------------------------------------------------------------
 * Timing
 * --------------------------------------------------------------- */

static double now_seconds(void)
{
    return (double)clock() / CLOCKS_PER_SEC;
}

/* ---------------------------------------------------------------
 * Utility
 * --------------------------------------------------------------- */

static void *checked_malloc(size_t size)
{
    void *p = malloc(size);

    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    return p;
}

static int random_value(void)
{
    return rand() % MAX_VALUE + 1;
}

/* ===============================================================
 * 1. UNSORTED ARRAY
 * =============================================================== */

static void ua_insert(int *a, int *n, int value)
{
    a[*n] = value;
    (*n)++;
}

static int *ua_search(int *a, int n, int key)
{
    for (int i = 0; i < n; i++) {
        if (a[i] == key)
            return &a[i];
    }

    return NULL;
}

/*
 * Delete is specified as Delete(D, x), where x is a pointer.
 * We therefore do not include the search for x in deletion.
 */
static void ua_delete(int *a, int *n, int *x)
{
    if (a == NULL || n == NULL || x == NULL || *n <= 0)
        return;

    int pos = (int)(x - a);

    if (pos < 0 || pos >= *n)
        return;

    for (int i = pos; i < *n - 1; i++)
        a[i] = a[i + 1];

    (*n)--;
}

static int *ua_minimum(int *a, int n)
{
    if (n <= 0)
        return NULL;

    int *best = &a[0];

    for (int i = 1; i < n; i++) {
        if (a[i] < *best)
            best = &a[i];
    }

    return best;
}

static int *ua_maximum(int *a, int n)
{
    if (n <= 0)
        return NULL;

    int *best = &a[0];

    for (int i = 1; i < n; i++) {
        if (a[i] > *best)
            best = &a[i];
    }

    return best;
}

/*
 * Dictionary predecessor:
 * largest key strictly smaller than x->key.
 */
static int *ua_predecessor(int *a, int n, int *x)
{
    if (a == NULL || n <= 0 || x == NULL)
        return NULL;

    int *pred = NULL;

    for (int i = 0; i < n; i++) {

        if (&a[i] == x)
            continue;

        if (a[i] < *x) {
            if (pred == NULL || a[i] > *pred)
                pred = &a[i];
        }
    }

    return pred;
}

/*
 * Dictionary successor:
 * smallest key strictly larger than x->key.
 */
static int *ua_successor(int *a, int n, int *x)
{
    if (a == NULL || n <= 0 || x == NULL)
        return NULL;

    int *succ = NULL;

    for (int i = 0; i < n; i++) {

        if (&a[i] == x)
            continue;

        if (a[i] > *x) {
            if (succ == NULL || a[i] < *succ)
                succ = &a[i];
        }
    }

    return succ;
}

/* ===============================================================
 * 2. SORTED ARRAY
 * =============================================================== */

static void sa_insert(int *a, int *n, int value)
{
    int i = *n - 1;

    while (i >= 0 && a[i] > value) {
        a[i + 1] = a[i];
        i--;
    }

    a[i + 1] = value;
    (*n)++;
}

static int *sa_search(int *a, int n, int key)
{
    int low = 0;
    int high = n - 1;

    while (low <= high) {

        int mid = low + (high - low) / 2;

        if (a[mid] == key)
            return &a[mid];

        if (a[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return NULL;
}

static void sa_delete(int *a, int *n, int *x)
{
    if (a == NULL || n == NULL || x == NULL || *n <= 0)
        return;

    int pos = (int)(x - a);

    if (pos < 0 || pos >= *n)
        return;

    for (int i = pos; i < *n - 1; i++)
        a[i] = a[i + 1];

    (*n)--;
}

static int *sa_minimum(int *a, int n)
{
    if (n <= 0)
        return NULL;

    return &a[0];
}

static int *sa_maximum(int *a, int n)
{
    if (n <= 0)
        return NULL;

    return &a[n - 1];
}

static int *sa_predecessor(int *a, int n, int *x)
{
    if (a == NULL || n <= 0 || x == NULL)
        return NULL;

    int pos = (int)(x - a);

    if (pos <= 0 || pos >= n)
        return NULL;

    return &a[pos - 1];
}

static int *sa_successor(int *a, int n, int *x)
{
    if (a == NULL || n <= 0 || x == NULL)
        return NULL;

    int pos = (int)(x - a);

    if (pos < 0 || pos >= n - 1)
        return NULL;

    return &a[pos + 1];
}

/* ===============================================================
 * 3. SINGLY LINKED UNSORTED LIST
 * =============================================================== */

typedef struct SNode {
    int key;
    struct SNode *next;
} SNode;

static SNode *sll_create_node(int key)
{
    SNode *node = checked_malloc(sizeof(SNode));

    node->key = key;
    node->next = NULL;

    return node;
}

static SNode *sllu_insert(SNode *head, int key)
{
    SNode *node = sll_create_node(key);

    node->next = head;

    return node;
}

static SNode *sllu_search(SNode *head, int key)
{
    SNode *cur = head;

    while (cur != NULL) {

        if (cur->key == key)
            return cur;

        cur = cur->next;
    }

    return NULL;
}

/*
 * Delete given pointer x.
 * Because this is a singly linked list, predecessor node
 * must be found by scanning from the head.
 */
static SNode *sllu_delete(SNode *head, SNode *x)
{
    if (head == NULL || x == NULL)
        return head;

    if (head == x) {
        SNode *new_head = head->next;
        free(head);
        return new_head;
    }

    SNode *cur = head;

    while (cur->next != NULL && cur->next != x)
        cur = cur->next;

    if (cur->next == x) {
        cur->next = x->next;
        free(x);
    }

    return head;
}

static SNode *sllu_minimum(SNode *head)
{
    if (head == NULL)
        return NULL;

    SNode *best = head;

    for (SNode *cur = head->next;
         cur != NULL;
         cur = cur->next) {

        if (cur->key < best->key)
            best = cur;
    }

    return best;
}

static SNode *sllu_maximum(SNode *head)
{
    if (head == NULL)
        return NULL;

    SNode *best = head;

    for (SNode *cur = head->next;
         cur != NULL;
         cur = cur->next) {

        if (cur->key > best->key)
            best = cur;
    }

    return best;
}

/*
 * IMPORTANT:
 *
 * For an UNSORTED linked list, x->next is NOT the dictionary
 * successor. We must find the smallest key greater than x->key.
 *
 * Therefore successor is O(n).
 */
static SNode *sllu_successor(SNode *head, SNode *x)
{
    if (head == NULL || x == NULL)
        return NULL;

    SNode *succ = NULL;

    for (SNode *cur = head; cur != NULL; cur = cur->next) {

        if (cur == x)
            continue;

        if (cur->key > x->key) {

            if (succ == NULL || cur->key < succ->key)
                succ = cur;
        }
    }

    return succ;
}

/*
 * IMPORTANT:
 *
 * For an UNSORTED linked list, the previous physical node is
 * NOT necessarily the dictionary predecessor.
 *
 * We find the largest key smaller than x->key.
 *
 * Therefore predecessor is O(n).
 */
static SNode *sllu_predecessor(SNode *head, SNode *x)
{
    if (head == NULL || x == NULL)
        return NULL;

    SNode *pred = NULL;

    for (SNode *cur = head; cur != NULL; cur = cur->next) {

        if (cur == x)
            continue;

        if (cur->key < x->key) {

            if (pred == NULL || cur->key > pred->key)
                pred = cur;
        }
    }

    return pred;
}

static void sllu_free(SNode *head)
{
    while (head != NULL) {

        SNode *next = head->next;

        free(head);

        head = next;
    }
}

/* ===============================================================
 * 4. SINGLY LINKED SORTED LIST
 * =============================================================== */

static SNode *slls_insert(SNode *head, int key)
{
    SNode *node = sll_create_node(key);

    if (head == NULL || key <= head->key) {
        node->next = head;
        return node;
    }

    SNode *cur = head;

    while (cur->next != NULL && cur->next->key < key)
        cur = cur->next;

    node->next = cur->next;
    cur->next = node;

    return head;
}

static SNode *slls_search(SNode *head, int key)
{
    SNode *cur = head;

    while (cur != NULL) {

        if (cur->key == key)
            return cur;

        if (cur->key > key)
            return NULL;

        cur = cur->next;
    }

    return NULL;
}

static SNode *slls_delete(SNode *head, SNode *x)
{
    return sllu_delete(head, x);
}

static SNode *slls_minimum(SNode *head)
{
    return head;
}

static SNode *slls_maximum(SNode *head)
{
    if (head == NULL)
        return NULL;

    SNode *cur = head;

    while (cur->next != NULL)
        cur = cur->next;

    return cur;
}

static SNode *slls_predecessor(SNode *head, SNode *x)
{
    if (head == NULL || x == NULL || head == x)
        return NULL;

    SNode *cur = head;

    while (cur != NULL && cur->next != x)
        cur = cur->next;

    return cur;
}

static SNode *slls_successor(SNode *x)
{
    if (x == NULL)
        return NULL;

    return x->next;
}

/* ===============================================================
 * 5 & 6. DOUBLY LINKED LIST
 * =============================================================== */

typedef struct DNode {
    int key;
    struct DNode *prev;
    struct DNode *next;
} DNode;

typedef struct {
    DNode *head;
    DNode *tail;
} DList;

static DNode *dll_create_node(int key)
{
    DNode *node = checked_malloc(sizeof(DNode));

    node->key = key;
    node->prev = NULL;
    node->next = NULL;

    return node;
}

static DList dll_create(void)
{
    DList list;

    list.head = NULL;
    list.tail = NULL;

    return list;
}

/* ---------------------- Unsorted DLL ------------------------- */

static void dllu_insert(DList *list, int key)
{
    DNode *node = dll_create_node(key);

    node->next = list->head;

    if (list->head != NULL)
        list->head->prev = node;
    else
        list->tail = node;

    list->head = node;
}

static DNode *dllu_search(DList *list, int key)
{
    DNode *cur = list->head;

    while (cur != NULL) {

        if (cur->key == key)
            return cur;

        cur = cur->next;
    }

    return NULL;
}

/*
 * Given x, deletion is O(1) in a DLL.
 */
static void dllu_delete(DList *list, DNode *x)
{
    if (list == NULL || x == NULL)
        return;

    if (x->prev != NULL)
        x->prev->next = x->next;
    else
        list->head = x->next;

    if (x->next != NULL)
        x->next->prev = x->prev;
    else
        list->tail = x->prev;

    free(x);
}

static DNode *dllu_minimum(DList *list)
{
    if (list == NULL || list->head == NULL)
        return NULL;

    DNode *best = list->head;

    for (DNode *cur = list->head->next;
         cur != NULL;
         cur = cur->next) {

        if (cur->key < best->key)
            best = cur;
    }

    return best;
}

static DNode *dllu_maximum(DList *list)
{
    if (list == NULL || list->head == NULL)
        return NULL;

    DNode *best = list->head;

    for (DNode *cur = list->head->next;
         cur != NULL;
         cur = cur->next) {

        if (cur->key > best->key)
            best = cur;
    }

    return best;
}

/*
 * IMPORTANT:
 *
 * x->prev is only the physical previous node.
 * In an UNSORTED DLL, that is NOT necessarily the dictionary
 * predecessor.
 *
 * Therefore we scan the list.
 */
static DNode *dllu_predecessor(DList *list, DNode *x)
{
    if (list == NULL || x == NULL)
        return NULL;

    DNode *pred = NULL;

    for (DNode *cur = list->head;
         cur != NULL;
         cur = cur->next) {

        if (cur == x)
            continue;

        if (cur->key < x->key) {

            if (pred == NULL || cur->key > pred->key)
                pred = cur;
        }
    }

    return pred;
}

/*
 * IMPORTANT:
 *
 * x->next is NOT the dictionary successor in an unsorted DLL.
 *
 * Therefore successor is O(n).
 */
static DNode *dllu_successor(DList *list, DNode *x)
{
    if (list == NULL || x == NULL)
        return NULL;

    DNode *succ = NULL;

    for (DNode *cur = list->head;
         cur != NULL;
         cur = cur->next) {

        if (cur == x)
            continue;

        if (cur->key > x->key) {

            if (succ == NULL || cur->key < succ->key)
                succ = cur;
        }
    }

    return succ;
}

/* ---------------------- Sorted DLL --------------------------- */

static void dlls_insert(DList *list, int key)
{
    DNode *node = dll_create_node(key);

    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
        return;
    }

    if (key <= list->head->key) {

        node->next = list->head;
        list->head->prev = node;
        list->head = node;

        return;
    }

    DNode *cur = list->head;

    while (cur->next != NULL && cur->next->key < key)
        cur = cur->next;

    node->next = cur->next;
    node->prev = cur;

    if (cur->next != NULL)
        cur->next->prev = node;
    else
        list->tail = node;

    cur->next = node;
}

static DNode *dlls_search(DList *list, int key)
{
    DNode *cur = list->head;

    while (cur != NULL) {

        if (cur->key == key)
            return cur;

        if (cur->key > key)
            return NULL;

        cur = cur->next;
    }

    return NULL;
}

static void dlls_delete(DList *list, DNode *x)
{
    dllu_delete(list, x);
}

static DNode *dlls_minimum(DList *list)
{
    if (list == NULL)
        return NULL;

    return list->head;
}

static DNode *dlls_maximum(DList *list)
{
    if (list == NULL)
        return NULL;

    return list->tail;
}

static DNode *dlls_predecessor(DNode *x)
{
    if (x == NULL)
        return NULL;

    return x->prev;
}

static DNode *dlls_successor(DNode *x)
{
    if (x == NULL)
        return NULL;

    return x->next;
}

static void dll_free(DList *list)
{
    if (list == NULL)
        return;

    DNode *cur = list->head;

    while (cur != NULL) {

        DNode *next = cur->next;

        free(cur);

        cur = next;
    }

    list->head = NULL;
    list->tail = NULL;
}

/* ===============================================================
 * BUILD ALL STRUCTURES
 * =============================================================== */

static void build_all(
    int *data,
    int n,
    int *ua,
    int *ua_n,
    int *sa,
    int *sa_n,
    SNode **sllu,
    SNode **slls,
    DList *dllu,
    DList *dlls
)
{
    *ua_n = 0;
    *sa_n = 0;

    *sllu = NULL;
    *slls = NULL;

    *dllu = dll_create();
    *dlls = dll_create();

    for (int i = 0; i < n; i++) {

        ua_insert(ua, ua_n, data[i]);

        sa_insert(sa, sa_n, data[i]);

        *sllu = sllu_insert(*sllu, data[i]);

        *slls = slls_insert(*slls, data[i]);

        dllu_insert(dllu, data[i]);

        dlls_insert(dlls, data[i]);
    }
}

/* ===============================================================
 * VALIDATION
 * =============================================================== */

static int is_sorted_array(int *a, int n)
{
    for (int i = 1; i < n; i++) {

        if (a[i - 1] > a[i])
            return 0;
    }

    return 1;
}

static int is_sorted_sll(SNode *head)
{
    for (SNode *cur = head;
         cur != NULL && cur->next != NULL;
         cur = cur->next) {

        if (cur->key > cur->next->key)
            return 0;
    }

    return 1;
}

static int is_sorted_dll(DList *list)
{
    if (list == NULL)
        return 1;

    for (DNode *cur = list->head;
         cur != NULL && cur->next != NULL;
         cur = cur->next) {

        if (cur->key > cur->next->key)
            return 0;

        if (cur->next->prev != cur)
            return 0;
    }

    return 1;
}

/* ===============================================================
 * FIND TEST ELEMENTS
 * =============================================================== */

/*
 * We deliberately select a middle element for predecessor and
 * successor measurements.
 *
 * Because duplicate random keys are possible, the data set is
 * generated from a permutation-like pattern below so that every
 * key is unique.
 */

static int *array_middle(int *a, int n)
{
    if (n <= 0)
        return NULL;

    return &a[n / 2];
}

static SNode *sll_middle(SNode *head, int n)
{
    if (head == NULL || n <= 0)
        return NULL;

    SNode *cur = head;

    for (int i = 0; i < n / 2 && cur != NULL; i++)
        cur = cur->next;

    return cur;
}

static DNode *dll_middle(DList *list, int n)
{
    if (list == NULL || list->head == NULL || n <= 0)
        return NULL;

    DNode *cur = list->head;

    for (int i = 0; i < n / 2 && cur != NULL; i++)
        cur = cur->next;

    return cur;
}

/* ===============================================================
 * REPETITION COUNTS
 * =============================================================== */

static int repetitions_for(int n)
{
    /*
     * Keep total work roughly manageable.
     */
    int reps = 20000 / n;

    if (reps < 10)
        reps = 10;

    if (reps > 1000)
        reps = 1000;

    return reps;
}

/* ===============================================================
 * BENCHMARK SEARCH
 * =============================================================== */

static double benchmark_search(
    int structure,
    int *ua,
    int ua_n,
    int *sa,
    int sa_n,
    SNode *sllu,
    SNode *slls,
    DList *dllu,
    DList *dlls,
    int n
)
{
    int reps = repetitions_for(n);

    volatile int sink = 0;

    /*
     * Key larger than all generated values.
     *
     * This forces:
     *   - full scan in unsorted structures
     *   - full traversal in sorted linked structures
     *   - O(log n) binary search in sorted array
     */
    int key = MAX_VALUE;

    double start = now_seconds();

    for (int r = 0; r < reps; r++) {

        switch (structure) {

            case 0: {
                int *p = ua_search(ua, ua_n, key);
                if (p != NULL)
                    sink += *p;
                break;
            }

            case 1: {
                int *p = sa_search(sa, sa_n, key);
                if (p != NULL)
                    sink += *p;
                break;
            }

            case 2: {
                SNode *p = sllu_search(sllu, key);
                if (p != NULL)
                    sink += p->key;
                break;
            }

            case 3: {
                SNode *p = slls_search(slls, key);
                if (p != NULL)
                    sink += p->key;
                break;
            }

            case 4: {
                DNode *p = dllu_search(dllu, key);
                if (p != NULL)
                    sink += p->key;
                break;
            }

            case 5: {
                DNode *p = dlls_search(dlls, key);
                if (p != NULL)
                    sink += p->key;
                break;
            }
        }
    }

    double end = now_seconds();

    if (sink == -123456)
        printf("%d\n", sink);

    return (end - start) / reps;
}

/* ===============================================================
 * BENCHMARK INSERT
 * =============================================================== */

static double benchmark_insert(
    int structure,
    int *data,
    int n
)
{
    int reps = 5;

    double total = 0.0;

    for (int r = 0; r < reps; r++) {

        int *ua = NULL;
        int *sa = NULL;

        SNode *sllu = NULL;
        SNode *slls = NULL;

        DList dllu = dll_create();
        DList dlls = dll_create();

        int ua_n = 0;
        int sa_n = 0;

        if (structure == 0)
            ua = checked_malloc((size_t)n * sizeof(int));

        if (structure == 1)
            sa = checked_malloc((size_t)n * sizeof(int));

        double start = now_seconds();

        for (int i = 0; i < n; i++) {

            switch (structure) {

                case 0:
                    ua_insert(ua, &ua_n, data[i]);
                    break;

                case 1:
                    sa_insert(sa, &sa_n, data[i]);
                    break;

                case 2:
                    sllu = sllu_insert(sllu, data[i]);
                    break;

                case 3:
                    slls = slls_insert(slls, data[i]);
                    break;

                case 4:
                    dllu_insert(&dllu, data[i]);
                    break;

                case 5:
                    dlls_insert(&dlls, data[i]);
                    break;
            }
        }

        double end = now_seconds();

        /*
         * Divide by n so the graph represents the average cost
         * of one insertion.
         */
        total += (end - start) / n;

        free(ua);
        free(sa);

        sllu_free(sllu);
        sllu_free(slls);

        dll_free(&dllu);
        dll_free(&dlls);
    }

    return total / reps;
}

/* ===============================================================
 * BENCHMARK DELETE
 * =============================================================== */

static double benchmark_delete(
    int structure,
    int *data,
    int n
)
{
    int reps = 3;

    double total = 0.0;

    for (int r = 0; r < reps; r++) {

        int *ua = NULL;
        int *sa = NULL;

        SNode *sllu = NULL;
        SNode *slls = NULL;

        DList dllu = dll_create();
        DList dlls = dll_create();

        int ua_n = 0;
        int sa_n = 0;

        /*
         * Build before timing.
         */
        if (structure == 0) {

            ua = checked_malloc((size_t)n * sizeof(int));

            for (int i = 0; i < n; i++)
                ua_insert(ua, &ua_n, data[i]);
        }

        else if (structure == 1) {

            sa = checked_malloc((size_t)n * sizeof(int));

            for (int i = 0; i < n; i++)
                sa_insert(sa, &sa_n, data[i]);
        }

        else if (structure == 2) {

            for (int i = 0; i < n; i++)
                sllu = sllu_insert(sllu, data[i]);
        }

        else if (structure == 3) {

            for (int i = 0; i < n; i++)
                slls = slls_insert(slls, data[i]);
        }

        else if (structure == 4) {

            for (int i = 0; i < n; i++)
                dllu_insert(&dllu, data[i]);
        }

        else if (structure == 5) {

            for (int i = 0; i < n; i++)
                dlls_insert(&dlls, data[i]);
        }

        double start = now_seconds();

        /*
         * Worst-case deletion.
         *
         * Array:
         *   delete first element -> O(n) shifting
         *
         * SLL:
         *   delete tail -> O(n) search for predecessor
         *
         * DLL:
         *   delete tail using its pointer -> O(1)
         */
        if (structure == 0) {

            while (ua_n > 0)
                ua_delete(ua, &ua_n, &ua[0]);
        }

        else if (structure == 1) {

            while (sa_n > 0)
                sa_delete(sa, &sa_n, &sa[0]);
        }

        else if (structure == 2) {

            while (sllu != NULL) {

                SNode *tail = sllu;

                while (tail->next != NULL)
                    tail = tail->next;

                sllu = sllu_delete(sllu, tail);
            }
        }

        else if (structure == 3) {

            while (slls != NULL) {

                SNode *tail = slls;

                while (tail->next != NULL)
                    tail = tail->next;

                slls = slls_delete(slls, tail);
            }
        }

        else if (structure == 4) {

            while (dllu.tail != NULL) {

                DNode *x = dllu.tail;

                dllu_delete(&dllu, x);
            }
        }

        else if (structure == 5) {

            while (dlls.tail != NULL) {

                DNode *x = dlls.tail;

                dlls_delete(&dlls, x);
            }
        }

        double end = now_seconds();

        /*
         * Average deletion time.
         */
        total += (end - start) / n;

        free(ua);
        free(sa);

        sllu_free(sllu);
        sllu_free(slls);

        dll_free(&dllu);
        dll_free(&dlls);
    }

    return total / reps;
}

/* ===============================================================
 * BENCHMARK MINIMUM
 * =============================================================== */

static double benchmark_minimum(
    int structure,
    int *ua,
    int ua_n,
    int *sa,
    int sa_n,
    SNode *sllu,
    SNode *slls,
    DList *dllu,
    DList *dlls,
    int n
)
{
    int reps = repetitions_for(n);

    volatile int sink = 0;

    double start = now_seconds();

    for (int r = 0; r < reps; r++) {

        switch (structure) {

            case 0: {
                int *p = ua_minimum(ua, ua_n);
                if (p)
                    sink += *p;
                break;
            }

            case 1: {
                int *p = sa_minimum(sa, sa_n);
                if (p)
                    sink += *p;
                break;
            }

            case 2: {
                SNode *p = sllu_minimum(sllu);
                if (p)
                    sink += p->key;
                break;
            }

            case 3: {
                SNode *p = slls_minimum(slls);
                if (p)
                    sink += p->key;
                break;
            }

            case 4: {
                DNode *p = dllu_minimum(dllu);
                if (p)
                    sink += p->key;
                break;
            }

            case 5: {
                DNode *p = dlls_minimum(dlls);
                if (p)
                    sink += p->key;
                break;
            }
        }
    }

    double end = now_seconds();

    if (sink == -123456)
        printf("%d\n", sink);

    return (end - start) / reps;
}

/* ===============================================================
 * BENCHMARK MAXIMUM
 * =============================================================== */

static double benchmark_maximum(
    int structure,
    int *ua,
    int ua_n,
    int *sa,
    int sa_n,
    SNode *sllu,
    SNode *slls,
    DList *dllu,
    DList *dlls,
    int n
)
{
    int reps = repetitions_for(n);

    volatile int sink = 0;

    double start = now_seconds();

    for (int r = 0; r < reps; r++) {

        switch (structure) {

            case 0: {
                int *p = ua_maximum(ua, ua_n);
                if (p)
                    sink += *p;
                break;
            }

            case 1: {
                int *p = sa_maximum(sa, sa_n);
                if (p)
                    sink += *p;
                break;
            }

            case 2: {
                SNode *p = sllu_maximum(sllu);
                if (p)
                    sink += p->key;
                break;
            }

            case 3: {
                SNode *p = slls_maximum(slls);
                if (p)
                    sink += p->key;
                break;
            }

            case 4: {
                DNode *p = dllu_maximum(dllu);
                if (p)
                    sink += p->key;
                break;
            }

            case 5: {
                DNode *p = dlls_maximum(dlls);
                if (p)
                    sink += p->key;
                break;
            }
        }
    }

    double end = now_seconds();

    if (sink == -123456)
        printf("%d\n", sink);

    return (end - start) / reps;
}

/* ===============================================================
 * BENCHMARK PREDECESSOR
 * =============================================================== */

static double benchmark_predecessor(
    int structure,
    int *ua,
    int ua_n,
    int *sa,
    int sa_n,
    SNode *sllu,
    SNode *slls,
    DList *dllu,
    DList *dlls,
    int n
)
{
    int reps = repetitions_for(n);

    volatile int sink = 0;

    int *ua_x = array_middle(ua, ua_n);
    int *sa_x = array_middle(sa, sa_n);

    SNode *sllu_x = sll_middle(sllu, n);
    SNode *slls_x = sll_middle(slls, n);

    DNode *dllu_x = dll_middle(dllu, n);
    DNode *dlls_x = dll_middle(dlls, n);

    double start = now_seconds();

    for (int r = 0; r < reps; r++) {

        switch (structure) {

            case 0: {
                int *p = ua_predecessor(ua, ua_n, ua_x);

                if (p)
                    sink += *p;

                break;
            }

            case 1: {
                int *p = sa_predecessor(sa, sa_n, sa_x);

                if (p)
                    sink += *p;

                break;
            }

            case 2: {
                /*
                 * CORRECT dictionary predecessor for UNSORTED SLL.
                 * O(n), not O(1).
                 */
                SNode *p = sllu_predecessor(sllu, sllu_x);

                if (p)
                    sink += p->key;

                break;
            }

            case 3: {
                /*
                 * Sorted SLL predecessor requires scanning from
                 * the head because there is no prev pointer.
                 */
                SNode *p = slls_predecessor(slls, slls_x);

                if (p)
                    sink += p->key;

                break;
            }

            case 4: {
                /*
                 * CORRECT dictionary predecessor for UNSORTED DLL.
                 * O(n), not O(1).
                 */
                DNode *p = dllu_predecessor(dllu, dllu_x);

                if (p)
                    sink += p->key;

                break;
            }

            case 5: {
                /*
                 * Sorted DLL predecessor is directly available.
                 * O(1).
                 */
                DNode *p = dlls_predecessor(dlls_x);

                if (p)
                    sink += p->key;

                break;
            }
        }
    }

    double end = now_seconds();

    if (sink == -123456)
        printf("%d\n", sink);

    return (end - start) / reps;
}

/* ===============================================================
 * BENCHMARK SUCCESSOR
 * =============================================================== */

static double benchmark_successor(
    int structure,
    int *ua,
    int ua_n,
    int *sa,
    int sa_n,
    SNode *sllu,
    SNode *slls,
    DList *dllu,
    DList *dlls,
    int n
)
{
    int reps = repetitions_for(n);

    volatile int sink = 0;

    int *ua_x = array_middle(ua, ua_n);
    int *sa_x = array_middle(sa, sa_n);

    SNode *sllu_x = sll_middle(sllu, n);
    SNode *slls_x = sll_middle(slls, n);

    DNode *dllu_x = dll_middle(dllu, n);
    DNode *dlls_x = dll_middle(dlls, n);

    double start = now_seconds();

    for (int r = 0; r < reps; r++) {

        switch (structure) {

            case 0: {
                int *p = ua_successor(ua, ua_n, ua_x);

                if (p)
                    sink += *p;

                break;
            }

            case 1: {
                int *p = sa_successor(sa, sa_n, sa_x);

                if (p)
                    sink += *p;

                break;
            }

            case 2: {
                /*
                 * CORRECT dictionary successor for UNSORTED SLL.
                 * O(n).
                 */
                SNode *p = sllu_successor(sllu, sllu_x);

                if (p)
                    sink += p->key;

                break;
            }

            case 3: {
                /*
                 * Sorted SLL successor is x->next.
                 * O(1).
                 */
                SNode *p = slls_successor(slls_x);

                if (p)
                    sink += p->key;

                break;
            }

            case 4: {
                /*
                 * CORRECT dictionary successor for UNSORTED DLL.
                 * O(n).
                 */
                DNode *p = dllu_successor(dllu, dllu_x);

                if (p)
                    sink += p->key;

                break;
            }

            case 5: {
                /*
                 * Sorted DLL successor is directly available.
                 * O(1).
                 */
                DNode *p = dlls_successor(dlls_x);

                if (p)
                    sink += p->key;

                break;
            }
        }
    }

    double end = now_seconds();

    if (sink == -123456)
        printf("%d\n", sink);

    return (end - start) / reps;
}

/* ===============================================================
 * THEORETICAL COMPLEXITY TABLE
 * =============================================================== */

static void print_complexity_table(void)
{
    printf("\n");
    printf("=====================================================================\n");
    printf("             THEORETICAL WORST-CASE COMPLEXITY\n");
    printf("=====================================================================\n");

    printf(
        "%-22s %-9s %-9s %-9s %-9s %-9s %-9s %-9s\n",
        "Structure",
        "Search",
        "Insert",
        "Delete",
        "Minimum",
        "Maximum",
        "Pred",
        "Succ"
    );

    printf(
        "%-22s %-9s %-9s %-9s %-9s %-9s %-9s %-9s\n",
        "Unsorted Array",
        "O(n)",
        "O(1)",
        "O(n)",
        "O(n)",
        "O(n)",
        "O(n)",
        "O(n)"
    );

    printf(
        "%-22s %-9s %-9s %-9s %-9s %-9s %-9s %-9s\n",
        "Sorted Array",
        "O(log n)",
        "O(n)",
        "O(n)",
        "O(1)",
        "O(1)",
        "O(1)",
        "O(1)"
    );

    printf(
        "%-22s %-9s %-9s %-9s %-9s %-9s %-9s %-9s\n",
        "SLL Unsorted",
        "O(n)",
        "O(1)",
        "O(n)",
        "O(n)",
        "O(n)",
        "O(n)",
        "O(n)"
    );

    printf(
        "%-22s %-9s %-9s %-9s %-9s %-9s %-9s %-9s\n",
        "SLL Sorted",
        "O(n)",
        "O(n)",
        "O(n)",
        "O(1)",
        "O(n)",
        "O(n)",
        "O(1)"
    );

    printf(
        "%-22s %-9s %-9s %-9s %-9s %-9s %-9s %-9s\n",
        "DLL Unsorted",
        "O(n)",
        "O(1)",
        "O(1)",
        "O(n)",
        "O(n)",
        "O(n)",
        "O(n)"
    );

    printf(
        "%-22s %-9s %-9s %-9s %-9s %-9s %-9s %-9s\n",
        "DLL Sorted",
        "O(n)",
        "O(n)",
        "O(1)",
        "O(1)",
        "O(1)",
        "O(1)",
        "O(1)"
    );

    printf("=====================================================================\n");
}

/* ===============================================================
 * SVG GRAPH HELPERS
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

/*
 * Fixed SVG line colors.
 * They are used only for distinguishing the six curves.
 */
static const char *svg_colors[STRUCTS] = {
    "#e41a1c",
    "#377eb8",
    "#4daf4a",
    "#984ea3",
    "#ff7f00",
    "#00a6a6"
};

/* ===============================================================
 * GENERATE SVG GRAPH
 * =============================================================== */

static void generate_svg_graph(
    const char *filename,
    const char *operation,
    double values[STRUCTS][NPTS],
    int sizes[NPTS]
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

    for (int s = 0; s < STRUCTS; s++) {
        for (int p = 0; p < NPTS; p++) {

            if (values[s][p] > max_value)
                max_value = values[s][p];
        }
    }

    if (max_value <= 0.0)
        max_value = 1.0;

    /*
     * Add some headroom.
     */
    max_value *= 1.10;

    fprintf(fp,
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");

    fprintf(fp,
        "<svg xmlns=\"http://www.w3.org/2000/svg\" "
        "width=\"%d\" height=\"%d\" "
        "viewBox=\"0 0 %d %d\">\n",
        GRAPH_WIDTH,
        GRAPH_HEIGHT,
        GRAPH_WIDTH,
        GRAPH_HEIGHT
    );

    fprintf(fp,
        "<rect x=\"0\" y=\"0\" width=\"%d\" height=\"%d\" "
        "fill=\"white\"/>\n",
        GRAPH_WIDTH,
        GRAPH_HEIGHT
    );

    /*
     * Title.
     */
    fprintf(fp,
        "<text x=\"%d\" y=\"40\" "
        "font-family=\"Arial\" font-size=\"24\" "
        "font-weight=\"bold\" text-anchor=\"middle\">",
        GRAPH_WIDTH / 2
    );

    svg_escape(fp, operation);

    fprintf(fp,
        " - Dictionary Operation Growth</text>\n"
    );

    /*
     * Grid lines.
     */
    for (int i = 0; i <= 5; i++) {

        double fraction = (double)i / 5.0;

        double y = plot_bottom - fraction * plot_height;

        fprintf(fp,
            "<line x1=\"%.2f\" y1=\"%.2f\" "
            "x2=\"%.2f\" y2=\"%.2f\" "
            "stroke=\"#dddddd\" stroke-width=\"1\"/>\n",
            (double)plot_left,
            y,
            (double)plot_right,
            y
        );

        double label = fraction * max_value;

        fprintf(fp,
            "<text x=\"%d\" y=\"%.2f\" "
            "font-family=\"Arial\" font-size=\"12\" "
            "text-anchor=\"end\">%.6g</text>\n",
            plot_left - 10,
            y + 4,
            label
        );
    }

    /*
     * X-axis tick labels.
     */
    for (int p = 0; p < NPTS; p++) {

        double fraction;

        if (NPTS == 1)
            fraction = 0.0;
        else
            fraction = (double)p / (NPTS - 1);

        double x = plot_left + fraction * plot_width;

        fprintf(fp,
            "<line x1=\"%.2f\" y1=\"%d\" "
            "x2=\"%.2f\" y2=\"%d\" "
            "stroke=\"#dddddd\" stroke-width=\"1\"/>\n",
            x,
            plot_top,
            x,
            plot_bottom
        );

        fprintf(fp,
            "<text x=\"%.2f\" y=\"%d\" "
            "font-family=\"Arial\" font-size=\"12\" "
            "text-anchor=\"middle\">%d</text>\n",
            x,
            plot_bottom + 22,
            sizes[p]
        );
    }

    /*
     * Axes.
     */
    fprintf(fp,
        "<line x1=\"%d\" y1=\"%d\" "
        "x2=\"%d\" y2=\"%d\" "
        "stroke=\"black\" stroke-width=\"2\"/>\n",
        plot_left,
        plot_bottom,
        plot_right,
        plot_bottom
    );

    fprintf(fp,
        "<line x1=\"%d\" y1=\"%d\" "
        "x2=\"%d\" y2=\"%d\" "
        "stroke=\"black\" stroke-width=\"2\"/>\n",
        plot_left,
        plot_bottom,
        plot_left,
        plot_top
    );

    /*
     * X-axis label.
     */
    fprintf(fp,
        "<text x=\"%d\" y=\"%d\" "
        "font-family=\"Arial\" font-size=\"16\" "
        "font-weight=\"bold\" text-anchor=\"middle\">"
        "Input Size (n)</text>\n",
        (plot_left + plot_right) / 2,
        GRAPH_HEIGHT - 25
    );

    /*
     * Y-axis label.
     */
    fprintf(fp,
        "<text x=\"25\" y=\"%d\" "
        "font-family=\"Arial\" font-size=\"16\" "
        "font-weight=\"bold\" "
        "transform=\"rotate(-90 25 %d)\" "
        "text-anchor=\"middle\">"
        "Average Time (seconds)</text>\n",
        (plot_top + plot_bottom) / 2,
        (plot_top + plot_bottom) / 2
    );

    /*
     * Plot six curves.
     */
    for (int s = 0; s < STRUCTS; s++) {

        fprintf(fp,
            "<polyline fill=\"none\" stroke=\"%s\" "
            "stroke-width=\"3\" points=\"",
            svg_colors[s]
        );

        for (int p = 0; p < NPTS; p++) {

            double x;

            if (NPTS == 1)
                x = plot_left;
            else
                x = plot_left +
                    ((double)p / (NPTS - 1)) * plot_width;

            double y =
                plot_bottom -
                (values[s][p] / max_value) * plot_height;

            fprintf(fp, "%.2f,%.2f ", x, y);
        }

        fprintf(fp, "\"/>\n");

        /*
         * Draw points.
         */
        for (int p = 0; p < NPTS; p++) {

            double x;

            if (NPTS == 1)
                x = plot_left;
            else
                x = plot_left +
                    ((double)p / (NPTS - 1)) * plot_width;

            double y =
                plot_bottom -
                (values[s][p] / max_value) * plot_height;

            fprintf(fp,
                "<circle cx=\"%.2f\" cy=\"%.2f\" r=\"4\" "
                "fill=\"%s\"/>\n",
                x,
                y,
                svg_colors[s]
            );
        }
    }

    /*
     * Legend.
     */
    int legend_x = plot_right + 25;
    int legend_y = plot_top + 20;

    fprintf(fp,
        "<text x=\"%d\" y=\"%d\" "
        "font-family=\"Arial\" font-size=\"15\" "
        "font-weight=\"bold\">Structures</text>\n",
        legend_x,
        legend_y
    );

    for (int s = 0; s < STRUCTS; s++) {

        int y = legend_y + 30 + s * 35;

        fprintf(fp,
            "<line x1=\"%d\" y1=\"%d\" "
            "x2=\"%d\" y2=\"%d\" "
            "stroke=\"%s\" stroke-width=\"4\"/>\n",
            legend_x,
            y,
            legend_x + 25,
            y,
            svg_colors[s]
        );

        fprintf(fp,
            "<text x=\"%d\" y=\"%d\" "
            "font-family=\"Arial\" font-size=\"12\">",
            legend_x + 35,
            y + 4
        );

        svg_escape(fp, structure_names[s]);

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
    srand(12345);

    /*
     * times[operation][structure][input size point]
     */
    double times[OPS][STRUCTS][NPTS];

    int sizes[NPTS];

    memset(times, 0, sizeof(times));

    print_complexity_table();

    printf("\n");
    printf("=====================================================================\n");
    printf("                 EXPERIMENTAL VALIDATION\n");
    printf("=====================================================================\n");

    /*
     * -------------------------------------------------------------
     * Run experiments for different input sizes.
     * -------------------------------------------------------------
     */

    for (int point = 0; point < NPTS; point++) {

        int n = START_N + point * STEP_N;

        sizes[point] = n;

        printf("\nInput size n = %d\n", n);

        /*
         * Generate UNIQUE keys.
         *
         * This avoids ambiguity when talking about immediate
         * predecessor/successor by key.
         */
        int *data =
            checked_malloc((size_t)n * sizeof(int));

        for (int i = 0; i < n; i++)
            data[i] = i + 1;

        /*
         * Shuffle the data so that:
         *
         * - unsorted structures are genuinely unsorted
         * - sorted structures must maintain their ordering
         */
        for (int i = n - 1; i > 0; i--) {

            int j = rand() % (i + 1);

            int temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }

        /*
         * Allocate arrays.
         */
        int *ua =
            checked_malloc((size_t)n * sizeof(int));

        int *sa =
            checked_malloc((size_t)n * sizeof(int));

        int ua_n;
        int sa_n;

        SNode *sllu;
        SNode *slls;

        DList dllu;
        DList dlls;

        /*
         * Build all six structures from the same input.
         */
        build_all(
            data,
            n,
            ua,
            &ua_n,
            sa,
            &sa_n,
            &sllu,
            &slls,
            &dllu,
            &dlls
        );

        /*
         * Validate sorted structures.
         */
        if (!is_sorted_array(sa, sa_n)) {
            fprintf(stderr,
                    "ERROR: Sorted array validation failed.\n");
            return EXIT_FAILURE;
        }

        if (!is_sorted_sll(slls)) {
            fprintf(stderr,
                    "ERROR: Sorted SLL validation failed.\n");
            return EXIT_FAILURE;
        }

        if (!is_sorted_dll(&dlls)) {
            fprintf(stderr,
                    "ERROR: Sorted DLL validation failed.\n");
            return EXIT_FAILURE;
        }

        /*
         * ---------------------------------------------------------
         * SEARCH
         * ---------------------------------------------------------
         */

        printf("  Search...\n");

        for (int s = 0; s < STRUCTS; s++) {

            times[0][s][point] =
                benchmark_search(
                    s,
                    ua,
                    ua_n,
                    sa,
                    sa_n,
                    sllu,
                    slls,
                    &dllu,
                    &dlls,
                    n
                );
        }

        /*
         * ---------------------------------------------------------
         * INSERT
         * ---------------------------------------------------------
         */

        printf("  Insert...\n");

        for (int s = 0; s < STRUCTS; s++) {

            times[1][s][point] =
                benchmark_insert(
                    s,
                    data,
                    n
                );
        }

        /*
         * ---------------------------------------------------------
         * DELETE
         * ---------------------------------------------------------
         */

        printf("  Delete...\n");

        for (int s = 0; s < STRUCTS; s++) {

            times[2][s][point] =
                benchmark_delete(
                    s,
                    data,
                    n
                );
        }

        /*
         * ---------------------------------------------------------
         * MINIMUM
         * ---------------------------------------------------------
         */

        printf("  Minimum...\n");

        for (int s = 0; s < STRUCTS; s++) {

            times[3][s][point] =
                benchmark_minimum(
                    s,
                    ua,
                    ua_n,
                    sa,
                    sa_n,
                    sllu,
                    slls,
                    &dllu,
                    &dlls,
                    n
                );
        }

        /*
         * ---------------------------------------------------------
         * MAXIMUM
         * ---------------------------------------------------------
         */

        printf("  Maximum...\n");

        for (int s = 0; s < STRUCTS; s++) {

            times[4][s][point] =
                benchmark_maximum(
                    s,
                    ua,
                    ua_n,
                    sa,
                    sa_n,
                    sllu,
                    slls,
                    &dllu,
                    &dlls,
                    n
                );
        }

        /*
         * ---------------------------------------------------------
         * PREDECESSOR
         * ---------------------------------------------------------
         */

        printf("  Predecessor...\n");

        for (int s = 0; s < STRUCTS; s++) {

            times[5][s][point] =
                benchmark_predecessor(
                    s,
                    ua,
                    ua_n,
                    sa,
                    sa_n,
                    sllu,
                    slls,
                    &dllu,
                    &dlls,
                    n
                );
        }

        /*
         * ---------------------------------------------------------
         * SUCCESSOR
         * ---------------------------------------------------------
         */

        printf("  Successor...\n");

        for (int s = 0; s < STRUCTS; s++) {

            times[6][s][point] =
                benchmark_successor(
                    s,
                    ua,
                    ua_n,
                    sa,
                    sa_n,
                    sllu,
                    slls,
                    &dllu,
                    &dlls,
                    n
                );
        }

        /*
         * Cleanup for this input size.
         */
        free(ua);
        free(sa);

        sllu_free(sllu);
        sllu_free(slls);

        dll_free(&dllu);
        dll_free(&dlls);

        free(data);
    }

    /*
     * =============================================================
     * PRINT EXPERIMENTAL RESULTS
     * =============================================================
     */

    printf("\n");
    printf("=====================================================================\n");
    printf("                     MEASURED TIMES\n");
    printf("=====================================================================\n");

    for (int op = 0; op < OPS; op++) {

        printf("\n%s\n", operation_names[op]);

        printf("%-22s", "Structure");

        for (int p = 0; p < NPTS; p++)
            printf("%12d", sizes[p]);

        printf("\n");

        for (int s = 0; s < STRUCTS; s++) {

            printf("%-22s", structure_names[s]);

            for (int p = 0; p < NPTS; p++) {

                printf(
                    "%12.8f",
                    times[op][s][p]
                );
            }

            printf("\n");
        }
    }

    /*
     * =============================================================
     * GENERATE GRAPH FILES
     * =============================================================
     */

    printf("\n");
    printf("=====================================================================\n");
    printf("                     GENERATING GRAPHS\n");
    printf("=====================================================================\n");

    for (int op = 0; op < OPS; op++) {

        generate_svg_graph(
            graph_files[op],
            operation_names[op],
            times[op],
            sizes
        );

        printf(
            "%-15s -> %s\n",
            operation_names[op],
            graph_files[op]
        );
    }

    /*
     * =============================================================
     * FINAL SUMMARY
     * =============================================================
     */

    printf("\n");
    printf("=====================================================================\n");
    printf("                         Q1 COMPLETE\n");
    printf("=====================================================================\n");

    printf("\nGenerated graphs:\n");

    for (int op = 0; op < OPS; op++)
        printf("  %s\n", graph_files[op]);

    printf("\nImportant corrected cases:\n");

    printf(
        "  SLL Unsorted predecessor : O(n)\n"
    );

    printf(
        "  SLL Unsorted successor   : O(n)\n"
    );

    printf(
        "  DLL Unsorted predecessor : O(n)\n"
    );

    printf(
        "  DLL Unsorted successor   : O(n)\n"
    );

    printf("\n");

    return 0;
}