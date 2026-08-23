#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int binarySearch(int arr[], int n, int key)
{
    int low = 0;
    int high = n - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == key)
            return 1;
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return 0;
}

/*
   Recursively choose k-1 elements.
   At the last step, binary search for required element.
*/
int findKSum(int arr[], int n, int k, int T,
             int start, int depth, int sum)
{
    // If k-1 elements have been selected
    if (depth == k - 1)
    {
        int required = T - sum;

        if (binarySearch(arr, n, required))
            return 1;

        return 0;
    }

    for (int i = start; i < n; i++)
    {
        if (findKSum(arr, n, k, T,
                     i + 1, depth + 1,
                     sum + arr[i]))
        {
            return 1;
        }
    }

    return 0;
}

int main()
{
    int n, k, T;

    printf("Enter number of elements n: ");
    scanf("%d", &n);

    int S[n];

    printf("Enter elements of S:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &S[i]);

    printf("Enter k: ");
    scanf("%d", &k);

    printf("Enter target T: ");
    scanf("%d", &T);

    // Sort array
    qsort(S, n, sizeof(int), compare);

    if (k > n || k < 2)
    {
        printf("Invalid value of k.\n");
        return 0;
    }

    if (findKSum(S, n, k, T, 0, 0, 0))
        printf("Yes, %d integers add up to %d.\n", k, T);
    else
        printf("No, %d integers do not add up to %d.\n", k, T);

    return 0;
}