#include <stdio.h>

#define MAX 1000

void push(long long h[], int *n, long long x) {
    int i = (*n)++;

    while (i > 0 && h[(i - 1) / 2] > x) {
        h[i] = h[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    h[i] = x;
}

long long pop(long long h[], int *n) {
    long long result = h[0];
    long long last = h[--(*n)];
    int i = 0;

    while (2 * i + 1 < *n) {
        int c = 2 * i + 1;

        if (c + 1 < *n && h[c + 1] < h[c])
            c++;

        if (last <= h[c])
            break;

        h[i] = h[c];
        i = c;
    }

    if (*n > 0)
        h[i] = last;

    return result;
}

int main() {
    long long h[MAX], total = 0;
    int n, i, size = 0;

    printf("Enter number of sticks: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Invalid number of sticks.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        long long x;

        scanf("%lld", &x);

        if (x < 0) {
            printf("Invalid stick length.\n");
            return 1;
        }

        push(h, &size, x);
    }

    while (size > 1) {
        long long x = pop(h, &size);
        long long y = pop(h, &size);
        long long sum = x + y;

        total += sum;
        push(h, &size, sum);
    }

    printf("Minimum total cost: %lld\n", total);

    return 0;
}