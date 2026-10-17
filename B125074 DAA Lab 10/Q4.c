#include <stdio.h>

#define MAX 100005

int parent[MAX], sz[MAX], active[MAX];
long long weight[MAX], sum[MAX];
int adj[MAX][1]; /* Not used: graph is stored as an edge list. */

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
    sum[a] += sum[b];
}

int main(void) {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++)
        scanf("%lld", &weight[i]);

    int *U = malloc((size_t)m * sizeof(int));
    int *V = malloc((size_t)m * sizeof(int));
    int *P = malloc((size_t)n * sizeof(int));
    long long *ans = malloc((size_t)(n + 1) * sizeof(long long));

    if (!U || !V || !P || !ans)
        return 1;

    for (int i = 0; i < m; i++)
        scanf("%d %d", &U[i], &V[i]);

    for (int i = 1; i <= n; i++)
        scanf("%d", &P[i]);

    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        sz[i] = 1;
        sum[i] = weight[i];
        active[i] = 0;
    }

    long long best = 0;
    ans[n] = 0;

    for (int i = n; i >= 1; i--) {
        /* Current graph has the first i deletions applied. */
        ans[i] = best;

        int x = P[i];
        active[x] = 1;
        parent[x] = x;
        sz[x] = 1;
        sum[x] = weight[x];

        for (int e = 0; e < m; e++) {
            int y = -1;
            if (U[e] == x) y = V[e];
            else if (V[e] == x) y = U[e];

            if (y != -1 && active[y])
                unite(x, y);
        }

        best = 0;
        for (int j = 1; j <= n; j++) {
            if (active[j] && find(j) == j && sum[j] > best)
                best = sum[j];
        }
    }

    for (int i = 1; i <= n; i++)
        printf("%lld\n", ans[i]);

    free(U);
    free(V);
    free(P);
    free(ans);
    return 0;
}