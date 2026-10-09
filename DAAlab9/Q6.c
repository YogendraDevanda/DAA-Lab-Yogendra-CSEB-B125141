#include <stdio.h>
#include <string.h>

#define MAX 10000
#define ALPHABET 52

typedef struct {
    int count;
    int character;
} Entry;

int indexOf(char c) {
    if (c >= 'A' && c <= 'Z')
        return c - 'A';

    if (c >= 'a' && c <= 'z')
        return c - 'a' + 26;

    return -1;
}

char charOf(int x) {
    return x < 26 ? 'A' + x : 'a' + x - 26;
}

int main() {
    char s[MAX], result[MAX];
    int freq[ALPHABET] = {0};
    int n, K, i, j;

    printf("Enter string: ");
    scanf("%9999s", s);

    printf("Enter K: ");
    scanf("%d", &K);

    n = (int)strlen(s);

    if (K < 0) {
        printf("Invalid K.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        int x = indexOf(s[i]);

        if (x < 0) {
            printf("Use English letters only.\n");
            return 1;
        }

        freq[x]++;
    }

    if (K <= 1) {
        printf("Reorganised string: %s\n", s);
        return 0;
    }

    for (i = 0; i < n; i++) {
        int best = -1;

        for (j = 0; j < ALPHABET; j++) {
            if (freq[j] > 0 &&
                (best == -1 || freq[j] > freq[best]))
                best = j;
        }

        if (best == -1) {
            printf("Reorganised string: %s\n", result);
            return 0;
        }

        result[i] = charOf(best);
        freq[best]--;

        if (freq[best] > 0) {
            int remaining = freq[best];
            int slots = n - i - 1;

            if (remaining > slots / K) {
                printf("No valid arrangement exists.\n");
                return 0;
            }
        }

        if (i >= K - 1) {
            int previous = indexOf(result[i - K + 1]);
            int current = indexOf(result[i]);

            if (previous == current) {
                printf("Greedy arrangement failed.\n");
                return 0;
            }
        }
    }

    result[n] = '\0';
    printf("Reorganised string: %s\n", result);

    return 0;
}