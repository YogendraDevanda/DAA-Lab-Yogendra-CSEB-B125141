#include <stdio.h>
#include <stdlib.h>

struct Interval
{
    int start;
    int end;
};

int compare(const void *a, const void *b)
{
    struct Interval *i1 = (struct Interval *)a;
    struct Interval *i2 = (struct Interval *)b;

    return i1->start - i2->start;
}

int main()
{
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    struct Interval arr[n];

    printf("Enter intervals:\n");

    for (int i = 0; i < n; i++)
    {
        printf("Interval %d: ", i + 1);
        scanf("%d %d", &arr[i].start, &arr[i].end);
    }

    // Sort intervals by starting point
    qsort(arr, n, sizeof(struct Interval), compare);

    printf("\nMerged intervals:\n");

    int currentStart = arr[0].start;
    int currentEnd = arr[0].end;

    for (int i = 1; i < n; i++)
    {
        // Overlapping
        if (arr[i].start <= currentEnd)
        {
            if (arr[i].end > currentEnd)
                currentEnd = arr[i].end;
        }
        else
        {
            // Print previous interval
            printf("(%d, %d)\n",
                   currentStart, currentEnd);

            currentStart = arr[i].start;
            currentEnd = arr[i].end;
        }
    }

    // Print last interval
    printf("(%d, %d)\n",
           currentStart, currentEnd);

    return 0;
}