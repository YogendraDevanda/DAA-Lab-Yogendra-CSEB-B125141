#include <stdio.h>

#define MAX 1000

typedef struct {
    int distance;
    int fuel;
} Station;

void sortStations(Station s[], int n) {
    int i, j;

    for (i = 1; i < n; i++) {
        Station key = s[i];
        j = i - 1;

        while (j >= 0 && s[j].distance > key.distance) {
            s[j + 1] = s[j];
            j--;
        }

        s[j + 1] = key;
    }
}

void push(int heap[], int *size, int value) {
    int i = (*size)++;

    while (i > 0 && heap[(i - 1) / 2] < value) {
        heap[i] = heap[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    heap[i] = value;
}

int pop(int heap[], int *size) {
    int result = heap[0];
    int last = heap[--(*size)];
    int i = 0;

    while (2 * i + 1 < *size) {
        int c = 2 * i + 1;

        if (c + 1 < *size && heap[c + 1] > heap[c])
            c++;

        if (last >= heap[c])
            break;

        heap[i] = heap[c];
        i = c;
    }

    if (*size > 0)
        heap[i] = last;

    return result;
}

int main() {
    Station s[MAX];
    int heap[MAX], size = 0;
    int n, D, fuel, i, stops = 0;

    printf("Enter destination, initial fuel and station count: ");
    scanf("%d %d %d", &D, &fuel, &n);

    if (n < 0 || n > MAX || D < 0 || fuel < 0) {
        printf("Invalid input.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("Enter station distance and fuel: ");
        scanf("%d %d", &s[i].distance, &s[i].fuel);

        if (s[i].distance < 0 || s[i].fuel < 0) {
            printf("Invalid station.\n");
            return 1;
        }
    }

    sortStations(s, n);

    for (i = 0; i <= n; i++) {
        int position = (i == n) ? D : s[i].distance;

        if (position > D) {
            printf("Invalid station distance.\n");
            return 1;
        }

        while (fuel < position) {
            if (size == 0) {
                printf("Destination unreachable.\n");
                return 0;
            }

            fuel += pop(heap, &size);
            stops++;
        }

        if (i < n)
            push(heap, &size, s[i].fuel);
    }

    printf("Minimum refuelling stops: %d\n", stops);

    return 0;
}