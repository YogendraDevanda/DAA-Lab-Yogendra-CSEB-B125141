#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    int n;

    printf("Enter number of people: ");
    scanf("%d", &n);

    int entry[n], exit[n];

    printf("Enter entry times:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Person %d: ", i + 1);
        scanf("%d", &entry[i]);
    }

    printf("Enter exit times:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Person %d: ", i + 1);
        scanf("%d", &exit[i]);
    }

    // Sort entry and exit times
    qsort(entry, n, sizeof(int), compare);
    qsort(exit, n, sizeof(int), compare);

    int i = 0;
    int j = 0;

    int current = 0;
    int maximum = 0;
    int maximumTime = 0;

    while (i < n && j < n)
    {
        if (entry[i] < exit[j])
        {
            current++;

            if (current > maximum)
            {
                maximum = current;
                maximumTime = entry[i];
            }

            i++;
        }
        else
        {
            current--;
            j++;
        }
    }

    printf("\nMaximum number of people = %d\n", maximum);
    printf("Time when maximum people are present = %d\n",
           maximumTime);

    return 0;
}