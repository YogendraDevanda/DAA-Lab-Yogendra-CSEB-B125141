#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

typedef struct {
    int start;
    int end;
} Meeting;

int compare(const void *a, const void *b) {
    const Meeting *x = a;
    const Meeting *y = b;

    if (x->start < y->start) return -1;
    if (x->start > y->start) return 1;
    return 0;
}

void push(int h[], int *n, int x) {
    int i = (*n)++;

    while (i > 0 && h[(i - 1) / 2] > x) {
        h[i] = h[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    h[i] = x;
}

int pop(int h[], int *n) {
    int result = h[0];
    int last = h[--(*n)];
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
    Meeting a[MAX];
    int heap[MAX], n, i, size = 0, rooms = 0;

    printf("Enter number of meetings: ");
    scanf("%d", &n);

    if (n < 0 || n > MAX) {
        printf("Invalid input.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        scanf("%d %d", &a[i].start, &a[i].end);

        if (a[i].end < a[i].start) {
            printf("Invalid interval.\n");
            return 1;
        }
    }

    qsort(a, n, sizeof(Meeting), compare);

    for (i = 0; i < n; i++) {
        if (size > 0 && heap[0] <= a[i].start)
            pop(heap, &size);

        push(heap, &size, a[i].end);

        if (size > rooms)
            rooms = size;
    }

    printf("Minimum number of meeting rooms: %d\n", rooms);

    return 0;
}