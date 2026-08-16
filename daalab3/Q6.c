#include <stdio.h>
#include <stdlib.h>

long comparisons = 0;

void selectionSort(int A[], int n)
{
    int i, j, min, temp;

    for (i = 0; i < n - 1; i++)
    {
        min = i;

        // Find the smallest element
        for (j = i + 1; j < n; j++)
        {
            comparisons++;

            if (A[j] < A[min])
            {
                min = j;
            }
        }

        // Exchange A[i] and A[min]
        temp = A[i];
        A[i] = A[min];
        A[min] = temp;
    }
}

/* Generate data and GNUPlot graph */
void generateGraph()
{
    FILE *data;
    FILE *plot;

    data = fopen("selection_data.txt", "w");

    if (data == NULL)
    {
        printf("Error creating data file!\n");
        return;
    }

    fprintf(data, "# n Actual_Comparisons Theoretical_Comparisons\n");

    for (int n = 10; n <= 1000; n += 10)
    {
        int *A = (int *)malloc(n * sizeof(int));

        if (A == NULL)
        {
            printf("Memory allocation failed!\n");
            fclose(data);
            return;
        }

        /*
           Use a sorted array.
           Even in the best case, Selection Sort
           performs the same number of comparisons.
        */
        for (int i = 0; i < n; i++)
        {
            A[i] = i + 1;
        }

        comparisons = 0;

        selectionSort(A, n);

        /*
           Theoretical comparisons:
           (n-1) + (n-2) + ... + 1
           = n(n-1)/2
        */
        long theoretical = (long)n * (n - 1) / 2;

        fprintf(data, "%d %ld %ld\n",
                n,
                comparisons,
                theoretical);

        free(A);
    }

    fclose(data);

    /* Create GNUPlot script */
    plot = fopen("selection_graph.plt", "w");

    if (plot == NULL)
    {
        printf("Error creating GNUPlot file!\n");
        return;
    }

    fprintf(plot, "set terminal png size 1000,600\n");
    fprintf(plot, "set output 'selection_graph.png'\n");

    fprintf(plot, "set title 'Selection Sort - Order of Growth'\n");
    fprintf(plot, "set xlabel 'Input Size (n)'\n");
    fprintf(plot, "set ylabel 'Number of Comparisons'\n");
    fprintf(plot, "set grid\n");

    fprintf(plot,
            "plot 'selection_data.txt' using 1:2 "
            "with linespoints title 'Actual Comparisons', "
            "'selection_data.txt' using 1:3 "
            "with lines title 'n(n-1)/2'\n");

    fclose(plot);

    /* Run GNUPlot */
    printf("\nGenerating graph using GNUPlot...\n");

    int result = system("gnuplot selection_graph.plt");

    if (result == 0)
    {
        printf("Graph generated successfully!\n");
        printf("File: selection_graph.png\n");
    }
    else
    {
        printf("GNUPlot failed to generate the graph.\n");
    }
}

int main()
{
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int A[n];

    printf("Enter the elements:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }

    comparisons = 0;

    selectionSort(A, n);

    printf("\nSorted array:\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }

    printf("\n");

    printf("\nNumber of comparisons = %ld\n", comparisons);

    printf("\nTime Complexity:\n");
    printf("Best Case    = Theta(n^2)\n");
    printf("Average Case = Theta(n^2)\n");
    printf("Worst Case   = Theta(n^2)\n");

    /* Generate graph */
    generateGraph();

    return 0;
}