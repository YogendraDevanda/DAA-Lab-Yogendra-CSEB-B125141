#include <stdio.h>
#include <stdlib.h>

struct Event
{
    int point;
    int type;
};

/*
   type = 1 -> start
   type = -1 -> end

   If points are equal:
   start should come before end.
*/
int compare(const void *a, const void *b)
{
    struct Event *e1 = (struct Event *)a;
    struct Event *e2 = (struct Event *)b;

    if (e1->point != e2->point)
        return e1->point - e2->point;

    return e2->type - e1->type;
}

int main()
{
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    struct Event events[2 * n];

    printf("Enter intervals:\n");

    for (int i = 0; i < n; i++)
    {
        int start, end;

        printf("Interval %d: ", i + 1);
        scanf("%d %d", &start, &end);

        events[2 * i].point = start;
        events[2 * i].type = 1;

        events[2 * i + 1].point = end;
        events[2 * i + 1].type = -1;
    }

    // Sort all events
    qsort(events, 2 * n, sizeof(struct Event), compare);

    int current = 0;
    int maximum = 0;
    int answerPoint = events[0].point;

    for (int i = 0; i < 2 * n; i++)
    {
        current += events[i].type;

        if (current > maximum)
        {
            maximum = current;
            answerPoint = events[i].point;
        }
    }

    printf("\nPoint with maximum overlap = %d\n",
           answerPoint);

    printf("Maximum number of intervals = %d\n",
           maximum);

    return 0;
}