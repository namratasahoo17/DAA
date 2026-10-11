#include <stdio.h>
#include <string.h>

#define MAX 10005

int main(void) {
    char s[MAX], result[MAX];
    int k;

    scanf("%10000s %d", s, &k);

    if (k <= 1) {
        printf("%s\n", s);
        return 0;
    }

    int freq[256] = {0};
    int nextAllowed[256] = {0};
    int n = (int)strlen(s);

    for (int i = 0; i < n; i++)
        freq[(unsigned char)s[i]]++;

    for (int pos = 0; pos < n; pos++) {
        int best = -1;

        for (int c = 0; c < 256; c++) {
            if (freq[c] > 0 && nextAllowed[c] <= pos &&
                (best == -1 || freq[c] > freq[best])) {
                best = c;
            }
        }

        if (best == -1) {
            printf("No valid arrangement found\n");
            return 0;
        }

        result[pos] = (char)best;
        freq[best]--;
        nextAllowed[best] = pos + k;
    }

    result[n] = '\0';
    printf("Reorganized string = %s\n", result);
    return 0;
}