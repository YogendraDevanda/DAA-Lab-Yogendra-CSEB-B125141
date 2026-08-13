#include <stdio.h>

void merge3(int arr[], int low, int mid1, int mid2, int high)
{
    int temp[high - low + 1];
    int i = low, j = mid1 + 1, k = mid2 + 1;
    int t = 0;

    while(i <= mid1 && j <= mid2 && k <= high)
    {
        if(arr[i] <= arr[j] && arr[i] <= arr[k])
            temp[t++] = arr[i++];
        else if(arr[j] <= arr[i] && arr[j] <= arr[k])
            temp[t++] = arr[j++];
        else
            temp[t++] = arr[k++];
    }

    while(i <= mid1 && j <= mid2)
    {
        if(arr[i] <= arr[j])
            temp[t++] = arr[i++];
        else
            temp[t++] = arr[j++];
    }

    while(j <= mid2 && k <= high)
    {
        if(arr[j] <= arr[k])
            temp[t++] = arr[j++];
        else
            temp[t++] = arr[k++];
    }

    while(i <= mid1 && k <= high)
    {
        if(arr[i] <= arr[k])
            temp[t++] = arr[i++];
        else
            temp[t++] = arr[k++];
    }

    while(i <= mid1)
        temp[t++] = arr[i++];

    while(j <= mid2)
        temp[t++] = arr[j++];

    while(k <= high)
        temp[t++] = arr[k++];

    for(i = low, t = 0; i <= high; i++, t++)
        arr[i] = temp[t];
}

void mergeSort3(int arr[], int low, int high)
{
    if(low < high)
    {
        int third = (high - low) / 3;
        int mid1 = low + third;
        int mid2 = low + 2 * third + 1;

        if(mid2 > high)
            mid2 = high;

        mergeSort3(arr, low, mid1);
        mergeSort3(arr, mid1 + 1, mid2);
        mergeSort3(arr, mid2 + 1, high);

        merge3(arr, low, mid1, mid2, high);
    }
}

int main()
{
    int n, i;

    printf("Enter size: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter elements:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    mergeSort3(arr, 0, n - 1);

    printf("Sorted Array:\n");
    for(i = 0; i < n; i++)
        printf("%d ", arr[i]);

    return 0;
}