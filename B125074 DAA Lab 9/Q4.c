#include <stdio.h>

typedef long long ll;

ll heap[200005];
int size = 0;

void push(ll x) {
    int i = size++;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p] <= x) break;
        heap[i] = heap[p];
        i = p;
    }
    heap[i] = x;
}

ll popMin(void) {
    ll ans = heap[0], last = heap[--size];
    int i = 0;

    while (2 * i + 1 < size) {
        int c = 2 * i + 1;
        if (c + 1 < size && heap[c + 1] < heap[c])
            c++;
        if (last <= heap[c]) break;
        heap[i] = heap[c];
        i = c;
    }
    if (size > 0) heap[i] = last;
    return ans;
}

int main(void) {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        ll x;
        scanf("%lld", &x);
        push(x);
    }

    ll totalCost = 0;

    while (size > 1) {
        ll a = popMin();
        ll b = popMin();
        ll combined = a + b;

        totalCost += combined;
        push(combined);
    }

    printf("Minimum total cost = %lld\n", totalCost);
    return 0;
}