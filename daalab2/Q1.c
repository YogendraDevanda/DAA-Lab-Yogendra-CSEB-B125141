#include <stdio.h>

#define MAX 1000

struct Item {
    int key;
};

/* Search */
int search(struct Item D[], int n, int key, int *comparisons) {

    *comparisons = 0;

    for (int i = 0; i < n; i++) {

        (*comparisons)++;

        if (D[i].key == key)
            return i;
    }

    return -1;
}

/* Insert */
void insert(struct Item D[], int *n, int key) {

    D[*n].key = key;
    (*n)++;
}

/* Delete */
void deleteItem(struct Item D[], int *n, int index) {

    D[index] = D[*n - 1];
    (*n)--;
}

/* Minimum */
int minimum(struct Item D[], int n, int *comparisons) {

    *comparisons = 0;

    int min = D[0].key;

    for (int i = 1; i < n; i++) {

        (*comparisons)++;

        if (D[i].key < min)
            min = D[i].key;
    }

    return min;
}

/* Maximum */
int maximum(struct Item D[], int n, int *comparisons) {

    *comparisons = 0;

    int max = D[0].key;

    for (int i = 1; i < n; i++) {

        (*comparisons)++;

        if (D[i].key > max)
            max = D[i].key;
    }

    return max;
}

/* Predecessor */
int predecessor(struct Item D[], int n, int key, int *comparisons) {

    *comparisons = 0;

    int pred = -1;

    for (int i = 0; i < n; i++) {

        (*comparisons)++;

        if (D[i].key < key) {

            if (pred == -1 || D[i].key > pred)
                pred = D[i].key;
        }
    }

    return pred;
}

/* Successor */
int successor(struct Item D[], int n, int key, int *comparisons) {

    *comparisons = 0;

    int succ = -1;

    for (int i = 0; i < n; i++) {

        (*comparisons)++;

        if (D[i].key > key) {

            if (succ == -1 || D[i].key < succ)
                succ = D[i].key;
        }
    }

    return succ;
}


int main() {

    struct Item D[MAX];

    int n;
    int key;
    int index;

    int searchComp;
    int minComp;
    int maxComp;
    int predComp;
    int succComp;


    /* ================= USER INPUT ================= */

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n >= MAX) {
        printf("Invalid number of elements!\n");
        return 1;
    }

    printf("Enter dictionary elements:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d", &D[i].key);
    }


    /* ================= DISPLAY ================= */

    printf("\nDictionary: ");

    for (int i = 0; i < n; i++) {
        printf("%d ", D[i].key);
    }


    /* ================= SEARCH ================= */

    printf("\n\nEnter key to search: ");
    scanf("%d", &key);

    index = search(D, n, key, &searchComp);

    if (index != -1)
        printf("Key found at index %d\n", index);
    else
        printf("Key not found\n");

    printf("Search comparisons = %d\n", searchComp);


    /* ================= INSERT ================= */

    printf("\nEnter key to insert: ");
    scanf("%d", &key);

    insert(D, &n, key);

    printf("After insertion: ");

    for (int i = 0; i < n; i++) {
        printf("%d ", D[i].key);
    }

    printf("\nInsert operations = 1\n");


    /* ================= DELETE ================= */

    printf("\nEnter key to delete: ");
    scanf("%d", &key);

    index = search(D, n, key, &searchComp);

    if (index != -1) {

        deleteItem(D, &n, index);

        printf("After deletion: ");

        for (int i = 0; i < n; i++) {
            printf("%d ", D[i].key);
        }

        printf("\nDelete search comparisons = %d\n", searchComp);
        printf("Actual Delete(D,x) operation = O(1)\n");

    } else {

        printf("Key not found\n");
    }


    /* ================= MINIMUM ================= */

    minComp = 0;

    int min = minimum(D, n, &minComp);

    printf("\nMinimum = %d", min);
    printf("\nMinimum comparisons = %d\n", minComp);


    /* ================= MAXIMUM ================= */

    maxComp = 0;

    int max = maximum(D, n, &maxComp);

    printf("\nMaximum = %d", max);
    printf("\nMaximum comparisons = %d\n", maxComp);


    /* ================= PREDECESSOR ================= */

    printf("\nEnter key for predecessor: ");
    scanf("%d", &key);

    int pred = predecessor(D, n, key, &predComp);

    if (pred != -1)
        printf("Predecessor = %d\n", pred);
    else
        printf("No predecessor exists\n");

    printf("Predecessor comparisons = %d\n", predComp);


    /* ================= SUCCESSOR ================= */

    printf("\nEnter key for successor: ");
    scanf("%d", &key);

    int succ = successor(D, n, key, &succComp);

    if (succ != -1)
        printf("Successor = %d\n", succ);
    else
        printf("No successor exists\n");

    printf("Successor comparisons = %d\n", succComp);


    /* =====================================================
                       CREATE DATA FILE
       ===================================================== */

    FILE *fp = fopen("dictionary_growth.dat", "w");

    if (fp == NULL) {

        printf("\nError creating dictionary_growth.dat\n");

        return 1;
    }



    for (int size = 10; size <= 1000; size += 10) {

        int searchGrowth = size;

        int insertGrowth = 1;

        int deleteGrowth = 1;

        int maximumGrowth = size - 1;

        int minimumGrowth = size - 1;

        int predecessorGrowth = size;

        int successorGrowth = size;


        fprintf(fp,
                "%d %d %d %d %d %d %d %d\n",
                size,
                searchGrowth,
                insertGrowth,
                deleteGrowth,
                maximumGrowth,
                minimumGrowth,
                predecessorGrowth,
                successorGrowth);
    }


    fclose(fp);


    printf("\n========================================\n");
    printf("dictionary_growth.dat created successfully!\n");
    printf("========================================\n");

    return 0;
}