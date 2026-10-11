#include <stdio.h>
#include <limits.h>

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
    int n;
    scanf("%d", &n);

    ll minimum = LLONG_MAX;

    for (int i = 0; i < n; i++) {
        ll x;
        scanf("%lld", &x);

        if (x % 2 != 0)
            x *= 2;

        push(x);
        if (x < minimum)
            minimum = x;
    }

    ll answer = LLONG_MAX;

    while (size > 0) {
        ll maximum = popMax();

        if (maximum - minimum < answer)
            answer = maximum - minimum;

        if (maximum % 2 != 0)
            break;

        maximum /= 2;

        if (maximum < minimum)
            minimum = maximum;

        push(maximum);
    }

    printf("Minimum deviation = %lld\n", answer);
    return 0;
}