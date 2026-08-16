#include <stdio.h>
#include <stdlib.h>

typedef struct Result
{
    int max;
    int min;
} Result;

/* Count comparisons */
long comparisons = 0;

/* Divide and Conquer Max-Min */
Result maxMin(int arr[], int low, int high)
{
    Result result, left, right;

    /* Only one element */
    if (low == high)
    {
        result.max = arr[low];
        result.min = arr[low];
        return result;
    }

    /* Two elements */
    if (high == low + 1)
    {
        comparisons++;

        if (arr[low] > arr[high])
        {
            result.max = arr[low];
            result.min = arr[high];
        }
        else
        {
            result.max = arr[high];
            result.min = arr[low];
        }

        return result;
    }

    /* Divide */
    int mid = (low + high) / 2;

    /* Conquer */
    left = maxMin(arr, low, mid);
    right = maxMin(arr, mid + 1, high);

    /* Combine - compare maximums */
    comparisons++;

    if (left.max > right.max)
        result.max = left.max;
    else
        result.max = right.max;

    /* Combine - compare minimums */
    comparisons++;

    if (left.min < right.min)
        result.min = left.min;
    else
        result.min = right.min;

    return result;
}

/* Generate data for GNUPlot */
void generateGraph()
{
    FILE *data;
    FILE *plot;

    data = fopen("maxmin_data.txt", "w");

    if (data == NULL)
    {
        printf("Error creating data file!\n");
        return;
    }

    fprintf(data, "# n Actual_Comparisons Theoretical_Comparisons\n");

    for (int n = 2; n <= 1000; n += 2)
    {
        int *arr = (int *)malloc(n * sizeof(int));

        if (arr == NULL)
        {
            printf("Memory allocation failed!\n");
            fclose(data);
            return;
        }

        /* Create array */
        for (int i = 0; i < n; i++)
        {
            arr[i] = i + 1;
        }

        comparisons = 0;

        maxMin(arr, 0, n - 1);

        /*
           Theoretical comparison bound:
           3n/2 - 2
        */
        double theoretical = (3.0 * n / 2.0) - 2;

        fprintf(data, "%d %ld %.0f\n",
                n,
                comparisons,
                theoretical);

        free(arr);
    }

    fclose(data);

    /* Create GNUPlot script */
    plot = fopen("maxmin_graph.plt", "w");

    if (plot == NULL)
    {
        printf("Error creating GNUPlot file!\n");
        return;
    }

    fprintf(plot, "set terminal png size 1000,600\n");
    fprintf(plot, "set output 'maxmin_graph.png'\n");

    fprintf(plot, "set title 'Maximum and Minimum using Divide and Conquer'\n");
    fprintf(plot, "set xlabel 'Input Size (n)'\n");
    fprintf(plot, "set ylabel 'Number of Comparisons'\n");

    fprintf(plot, "set grid\n");

    fprintf(plot,
            "plot 'maxmin_data.txt' using 1:2 "
            "with linespoints title 'Actual Comparisons', "
            "'maxmin_data.txt' using 1:3 "
            "with lines title '3n/2 - 2'\n");

    fclose(plot);

    /* Run GNUPlot */
    printf("\nGenerating graph using GNUPlot...\n");

    int result = system("gnuplot maxmin_graph.plt");

    if (result == 0)
    {
        printf("Graph generated successfully!\n");
        printf("File: maxmin_graph.png\n");
    }
    else
    {
        printf("GNUPlot failed to generate the graph.\n");
    }
}

int main()
{
    int n;

    printf("Enter size of array: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    comparisons = 0;

    Result result = maxMin(arr, 0, n - 1);

    printf("\nMaximum element = %d\n", result.max);
    printf("Minimum element = %d\n", result.min);

    printf("Number of comparisons = %ld\n", comparisons);

    printf("\nTime Complexity = Theta(n)\n");
    printf("Comparison Bound = 3n/2 - 2\n");

    /* Generate graph */
    generateGraph();

    return 0;
}