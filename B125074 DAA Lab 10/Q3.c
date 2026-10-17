#include <stdio.h>

#define MAX 100005

int parent[MAX], sz[MAX];
long long weight[MAX], sum[MAX];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void addEdge(int u, int v) {
    u = find(u);
    v = find(v);

    if (u == v)
        return;

    if (sz[u] < sz[v]) {
        int t = u;
        u = v;
        v = t;
    }

    parent[v] = u;
    sz[u] += sz[v];
    sum[u] += sum[v];
}

long long maximumWeight(int n, int K) {
    long long best = 0;

    for (int i = 1; i <= n; i++) {
        if (find(i) == i && sz[i] <= K && sum[i] > best)
            best = sum[i];
    }

    return best;
}

int main(void) {
    int n, m, K;
    scanf("%d %d %d", &n, &m, &K);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", &weight[i]);
        parent[i] = i;
        sz[i] = 1;
        sum[i] = weight[i];
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        addEdge(u, v);
        printf("%lld\n", maximumWeight(n, K));
    }

    return 0;
}