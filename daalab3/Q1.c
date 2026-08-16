#include <stdio.h>
#include <stdlib.h>

int binarySearch(int arr[], int n, int x, int *comparisons)
{
    int p = 0, r = n - 1;

    while (p <= r)
    {
        int mid = (p + r) / 2;

        (*comparisons)++;

        if (arr[mid] == x)
            return mid;

        if (x < arr[mid])
            r = mid - 1;
        else
            p = mid + 1;
    }

    return -1;
}

int ternarySearch(int arr[], int n, int x, int *comparisons)
{
    int p = 0, r = n - 1;

    while (p <= r)
    {
        int mid1 = p + (r - p) / 3;
        int mid2 = r - (r - p) / 3;

        (*comparisons)++;

        if (arr[mid1] == x)
            return mid1;

        (*comparisons)++;

        if (arr[mid2] == x)
            return mid2;

        if (x < arr[mid1])
            r = mid1 - 1;
        else if (x > arr[mid2])
            p = mid2 + 1;
        else
        {
            p = mid1 + 1;
            r = mid2 - 1;
        }
    }

    return -1;
}

/* Function to generate data and create graph */
void generateGraph()
{
    FILE *data;
    FILE *plot;

    data = fopen("search_data.txt", "w");

    if (data == NULL)
    {
        printf("Error creating data file!\n");
        return;
    }

    fprintf(data, "# n Binary_Search Ternary_Search\n");

    for (int n = 10; n <= 1000; n += 10)
    {
        int *arr = (int *)malloc(n * sizeof(int));

        if (arr == NULL)
        {
            printf("Memory allocation failed!\n");
            fclose(data);
            return;
        }

        /* Sorted array */
        for (int i = 0; i < n; i++)
        {
            arr[i] = i;
        }

        /*
           x = n + 1 means element is not present.
           This gives a good worst-case comparison count.
        */
        int x = n + 1;

        int binaryComparisons = 0;
        int ternaryComparisons = 0;

        binarySearch(arr, n, x, &binaryComparisons);
        ternarySearch(arr, n, x, &ternaryComparisons);

        fprintf(data, "%d %d %d\n",
                n,
                binaryComparisons,
                ternaryComparisons);

        free(arr);
    }

    fclose(data);

    /* Create GNUPlot script */
    plot = fopen("search_graph.plt", "w");

    if (plot == NULL)
    {
        printf("Error creating GNUPlot file!\n");
        return;
    }

    fprintf(plot, "set terminal png size 1000,600\n");
    fprintf(plot, "set output 'search_graph.png'\n");

    fprintf(plot, "set title 'Binary Search vs Ternary Search'\n");
    fprintf(plot, "set xlabel 'Input Size (n)'\n");
    fprintf(plot, "set ylabel 'Number of Comparisons'\n");

    fprintf(plot, "set grid\n");

    fprintf(plot,
            "plot 'search_data.txt' using 1:2 "
            "with linespoints title 'Binary Search', "
            "'search_data.txt' using 1:3 "
            "with linespoints title 'Ternary Search'\n");

    fclose(plot);

    /* Run GNUPlot */
    printf("\nGenerating graph using GNUPlot...\n");

    system("gnuplot search_graph.plt");

    printf("Graph generated successfully!\n");
    printf("File: search_graph.png\n");
}

int main()
{
    int n, x;

    printf("Enter size of array: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));

    if (arr == NULL)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter elements of array:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("Enter element to search: ");
    scanf("%d", &x);

    int binaryComparisons = 0;
    int ternaryComparisons = 0;

    int b = binarySearch(arr, n, x, &binaryComparisons);
    int t = ternarySearch(arr, n, x, &ternaryComparisons);

    printf("\n========== Binary Search ==========\n");

    if (b != -1)
        printf("Element found at index %d\n", b);
    else
        printf("Element not found\n");

    printf("Comparisons = %d\n", binaryComparisons);

    printf("\n========== Ternary Search ==========\n");

    if (t != -1)
        printf("Element found at index %d\n", t);
    else
        printf("Element not found\n");

    printf("Comparisons = %d\n", ternaryComparisons);

    printf("\n========== Time Complexity ==========\n");
    printf("Binary Search  : O(log2 n)\n");
    printf("Ternary Search : O(log3 n)\n");

    /* Generate graph */
    generateGraph();

    free(arr);

    return 0;
}