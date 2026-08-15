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
    int result[k * n];
    int temp[k * n];

    printf("Enter sorted arrays:\n");

    for (int i = 0; i < k; i++)
    {
        printf("Array %d: ", i + 1);

        for (int j = 0; j < n; j++)
            scanf("%d", &arr[i][j]);
    }

    // First array becomes the initial result
    for (int i = 0; i < n; i++)
        result[i] = arr[0][i];

    int resultSize = n;

    // Merge remaining arrays one by one
    for (int i = 1; i < k; i++)
    {
        merge(result, resultSize, arr[i], n, temp);

        resultSize = resultSize + n;

        for (int j = 0; j < resultSize; j++)
            result[j] = temp[j];
    }

    printf("\nFinal sorted array:\n");

    for (int i = 0; i < resultSize; i++)
        printf("%d ", result[i]);

    return 0;
}