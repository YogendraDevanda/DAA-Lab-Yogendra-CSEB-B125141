#include <stdio.h>

void merge(int a[], int n1, int b[], int n2, int result[])
{
    int i = 0, j = 0, k = 0;

    while (i < n1 && j < n2)
    {
        if (a[i] <= b[j])
            result[k++] = a[i++];
        else
            result[k++] = b[j++];
    }

    while (i < n1)
        result[k++] = a[i++];

    while (j < n2)
        result[k++] = b[j++];
}

int main()
{
    int k, n;

    printf("Enter number of arrays (k): ");
    scanf("%d", &k);

    printf("Enter number of elements in each array (n): ");
    scanf("%d", &n);

    int arr[k][n];

    printf("Enter sorted arrays:\n");

    for (int i = 0; i < k; i++)
    {
        printf("Array %d: ", i + 1);

        for (int j = 0; j < n; j++)
            scanf("%d", &arr[i][j]);
    }

    // Each array is stored as a separate block
    int current[k * n];

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
            current[i * n + j] = arr[i][j];
    }

    int numberOfArrays = k;
    int size = n;

    while (numberOfArrays > 1)
    {
        int next[k * n];
        int newNumber = 0;

        for (int i = 0; i < numberOfArrays; i += 2)
        {
            if (i + 1 < numberOfArrays)
            {
                merge(
                    &current[i * size],
                    size,
                    &current[(i + 1) * size],
                    size,
                    &next[newNumber * 2 * size]
                );

                newNumber++;
            }
            else
            {
                // If one array is left, copy it
                for (int j = 0; j < size; j++)
                    next[newNumber * 2 * size + j] =
                        current[i * size + j];

                newNumber++;
            }
        }

        // Copy next level back to current
        int totalElements = 0;

        for (int i = 0; i < newNumber; i++)
        {
            int blockSize = (i * 2 + 2 <= numberOfArrays)
                            ? 2 * size
                            : size;

            for (int j = 0; j < blockSize; j++)
                current[totalElements++] =
                    next[i * 2 * size + j];
        }

        size = size * 2;
        numberOfArrays = newNumber;
    }

    printf("\nFinal sorted array:\n");

    for (int i = 0; i < k * n; i++)
        printf("%d ", current[i]);

    return 0;
}