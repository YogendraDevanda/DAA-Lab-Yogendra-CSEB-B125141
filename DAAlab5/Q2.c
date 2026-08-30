#include <stdio.h>

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    int temp;

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;

            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

int quickSelect(int arr[], int low, int high, int k)
{
    if (low <= high)
    {
        int pos = partition(arr, low, high);

        if (pos == k)
            return arr[pos];

        if (k < pos)
            return quickSelect(arr, low, pos - 1, k);

        return quickSelect(arr, pos + 1, high, k);
    }

    return -1;
}

int main()
{
    int n, k;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter K: ");
    scanf("%d", &k);

    if (k < 1 || k > n)
    {
        printf("Invalid value of K\n");
        return 0;
    }

    int result = quickSelect(arr, 0, n - 1, k - 1);

    printf("%d'th smallest element = %d\n", k, result);

    return 0;
}