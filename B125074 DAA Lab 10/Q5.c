#include <stdio.h>
#include <stdlib.h>

#define MAX 100005

int parent[MAX], sz[MAX], A[MAX];

typedef struct {
    int root, index, value;
} Item;

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b)
        return;

    if (sz[a] < sz[b]) {
        int t = a;
        a = b;
        b = t;
    }

    parent[b] = a;
    sz[a] += sz[b];
}

int cmpIndex(const void *a, const void *b) {
    const Item *x = a, *y = b;

    if (x->root != y->root)
        return (x->root > y->root) - (x->root < y->root);

    return (x->index > y->index) - (x->index < y->index);
}

int cmpValue(const void *a, const void *b) {
    const Item *x = a, *y = b;

    if (x->root != y->root)
        return (x->root > y->root) - (x->root < y->root);

    return (x->value > y->value) - (x->value < y->value);
}

int main(void) {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &A[i]);
        parent[i] = i;
        sz[i] = 1;
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        unite(u, v);
    }

    Item *byIndex = malloc((size_t)n * sizeof(Item));
    Item *byValue = malloc((size_t)n * sizeof(Item));

    if (!byIndex || !byValue)
        return 1;

    for (int i = 1; i <= n; i++) {
        int root = find(i);
        byIndex[i - 1] = (Item){root, i, A[i]};
        byValue[i - 1] = (Item){root, i, A[i]};
    }

    qsort(byIndex, n, sizeof(Item), cmpIndex);
    qsort(byValue, n, sizeof(Item), cmpValue);

    for (int i = 0; i < n; i++)
        A[byIndex[i].index] = byValue[i].value;

    for (int i = 1; i <= n; i++)
        printf("%d%c", A[i], i == n ? '\n' : ' ');

    free(byIndex);
    free(byValue);
    return 0;
}