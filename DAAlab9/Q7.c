#include <stdio.h>

#define MAX 100000

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void downHeap(int h[], int n, int i) {
    while (1) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < n && h[l] > h[largest])
            largest = l;

        if (r < n && h[r] > h[largest])
            largest = r;

        if (largest == i)
            break;

        swap(&h[i], &h[largest]);
        i = largest;
    }
}

void buildHeap(int h[], int n) {
    int i;

    for (i = n / 2 - 1; i >= 0; i--)
        downHeap(h, n, i);
}

int main() {
    int a[MAX], n, i;
    int minimum = 2147483647;
    long long answer;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Invalid input.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);

        if (a[i] <= 0 || a[i] > 1073741823) {
            printf("Values must be positive and within range.\n");
            return 1;
        }

        if (a[i] % 2 == 1)
            a[i] *= 2;

        if (a[i] < minimum)
            minimum = a[i];
    }

    buildHeap(a, n);

    answer = (long long)a[0] - minimum;

    while (a[0] % 2 == 0) {
        int maximum = a[0] / 2;

        a[0] = maximum;

        if (maximum < minimum)
            minimum = maximum;

        downHeap(a, n, 0);

        if ((long long)a[0] - minimum < answer)
            answer = (long long)a[0] - minimum;
    }

    printf("Minimum deviation: %lld\n", answer);

    return 0;
}