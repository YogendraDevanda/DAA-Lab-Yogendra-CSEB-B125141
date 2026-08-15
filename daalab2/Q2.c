#include <stdio.h>
#include <stdlib.h>

long long mergeComparisons = 0;
long long threeWayComparisons = 0;

/* ---------- NORMAL MERGE SORT ---------- */

void merge(int arr[], int left, int mid, int right) {

    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {

        mergeComparisons++;

        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(int arr[], int left, int right) {

    if (left < right) {

        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}


/* ---------- THREE-WAY MERGE SORT ---------- */

void mergeThree(int arr[], int left, int mid1, int mid2, int right) {

    int n = right - left + 1;

    int *temp = malloc(n * sizeof(int));

    int i = left;
    int j = mid1 + 1;
    int k = mid2 + 1;
    int p = 0;

    while (i <= mid1 || j <= mid2 || k <= right) {

        int choice;

        /* Only third part available */
        if (i > mid1 && j > mid2) {
            choice = 3;
        }

        /* First and second part available */
        else if (k > right) {

            if (i > mid1)
                choice = 2;

            else if (j > mid2)
                choice = 1;

            else {
                threeWayComparisons++;

                if (arr[i] <= arr[j])
                    choice = 1;
                else
                    choice = 2;
            }
        }

        /* First and third part available */
        else if (j > mid2) {

            if (i > mid1)
                choice = 3;

            else {
                threeWayComparisons++;

                if (arr[i] <= arr[k])
                    choice = 1;
                else
                    choice = 3;
            }
        }

        /* Second and third part available */
        else if (i > mid1) {

            threeWayComparisons++;

            if (arr[j] <= arr[k])
                choice = 2;
            else
                choice = 3;
        }

        /* All three parts available */
        else {

            threeWayComparisons += 2;

            if (arr[i] <= arr[j] && arr[i] <= arr[k])
                choice = 1;

            else if (arr[j] <= arr[k])
                choice = 2;

            else
                choice = 3;
        }

        if (choice == 1)
            temp[p++] = arr[i++];

        else if (choice == 2)
            temp[p++] = arr[j++];

        else
            temp[p++] = arr[k++];
    }

    for (int x = 0; x < n; x++)
        arr[left + x] = temp[x];

    free(temp);
}

void threeWayMergeSort(int arr[], int left, int right) {

    int n = right - left + 1;

    if (n <= 1)
        return;

    if (n == 2) {

        threeWayComparisons++;

        if (arr[left] > arr[right]) {

            int temp = arr[left];

            arr[left] = arr[right];
            arr[right] = temp;
        }

        return;
    }

    int third = n / 3;

    int mid1 = left + third - 1;
    int mid2 = left + 2 * third - 1;

    /* Handle small sizes */
    if (third == 0)
        third = 1;

    mid1 = left + third - 1;

    mid2 = left + 2 * third - 1;

    if (mid2 >= right)
        mid2 = right - 1;

    threeWayMergeSort(arr, left, mid1);

    threeWayMergeSort(arr, mid1 + 1, mid2);

    threeWayMergeSort(arr, mid2 + 1, right);

    mergeThree(arr, left, mid1, mid2, right);
}


/* ---------- MAIN ---------- */

int main() {

    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of elements.\n");
        return 1;
    }

    int *arr1 = malloc(n * sizeof(int));
    int *arr2 = malloc(n * sizeof(int));

    if (arr1 == NULL || arr2 == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++) {

        scanf("%d", &arr1[i]);

        arr2[i] = arr1[i];
    }


    /* Normal Merge Sort */

    mergeComparisons = 0;

    mergeSort(arr1, 0, n - 1);

    printf("\nNormal Merge Sort:\n");

    printf("Comparisons = %lld\n", mergeComparisons);

    printf("Sorted array: ");

    for (int i = 0; i < n; i++)
        printf("%d ", arr1[i]);


    /* Three-Way Merge Sort */

    threeWayComparisons = 0;

    threeWayMergeSort(arr2, 0, n - 1);

    printf("\n\nModified 3-Way Merge Sort:\n");

    printf("Comparisons = %lld\n", threeWayComparisons);

    printf("Sorted array: ");

    for (int i = 0; i < n; i++)
        printf("%d ", arr2[i]);


    /* ---------- CREATE DATA FILE ---------- */

    FILE *fp = fopen("merge_sort_growth.dat", "w");

    if (fp == NULL) {

        printf("\nError creating data file.\n");

        free(arr1);
        free(arr2);

        return 1;
    }


    /*
       Columns:

       1 = Input size
       2 = Normal Merge Sort comparisons
       3 = 3-Way Merge Sort comparisons
    */

    for (int size = 10; size <= 1000; size += 10) {

        int *a = malloc(size * sizeof(int));
        int *b = malloc(size * sizeof(int));

        if (a == NULL || b == NULL)
            break;

        /*
           Descending input gives a large
           comparison workload.
        */

        for (int i = 0; i < size; i++) {

            a[i] = size - i;
            b[i] = size - i;
        }


        /* Normal Merge Sort */

        mergeComparisons = 0;

        mergeSort(a, 0, size - 1);

        long long normal = mergeComparisons;


        /* Three-Way Merge Sort */

        threeWayComparisons = 0;

        threeWayMergeSort(b, 0, size - 1);

        long long modified = threeWayComparisons;


        /* Write to data file */

        fprintf(fp, "%d %lld %lld\n",
                size,
                normal,
                modified);


        free(a);
        free(b);
    }

    fclose(fp);


    printf("\n\n====================================\n");
    printf("Data file created successfully!\n");
    printf("File: merge_sort_growth.dat\n");
    printf("====================================\n");


    free(arr1);
    free(arr2);

    return 0;
}