#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

ll heap[200005];
int size = 0;

void push(ll x) {
    int i = size++;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p] >= x) break;
        heap[i] = heap[p];
        i = p;
    }
    heap[i] = x;
}

ll popMax(void) {
    ll ans = heap[0], last = heap[--size];
    int i = 0;

    while (2 * i + 1 < size) {
        int c = 2 * i + 1;
        if (c + 1 < size && heap[c + 1] > heap[c])
            c++;
        if (last >= heap[c]) break;
        heap[i] = heap[c];
        i = c;
    }
    if (size > 0) heap[i] = last;
    return ans;
}

int main(void) {
    ll target, fuel;
    int n;
    scanf("%lld %lld %d", &target, &fuel, &n);

    ll *dist = malloc(n * sizeof(ll));
    ll *gas = malloc(n * sizeof(ll));

    for (int i = 0; i < n; i++)
        scanf("%lld %lld", &dist[i], &gas[i]);

    ll reach = fuel;
    int i = 0, stops = 0;

    while (reach < target) {
        while (i < n && dist[i] <= reach) {
            push(gas[i]);
            i++;
        }

        if (size == 0) {
            printf("Impossible to reach target\n");
            free(dist);
            free(gas);
            return 0;
        }

        reach += popMax();
        stops++;
    }

    printf("Minimum refuelling stops = %d\n", stops);

    free(dist);
    free(gas);
    return 0;
}