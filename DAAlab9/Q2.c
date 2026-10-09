#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256

typedef struct Node {
    int freq;
    int minSymbol;
    int symbol;
    struct Node *left, *right;
} Node;

Node *newNode(int freq, int symbol, int minSymbol,
              Node *left, Node *right) {
    Node *p = malloc(sizeof(Node));

    if (!p) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    p->freq = freq;
    p->symbol = symbol;
    p->minSymbol = minSymbol;
    p->left = left;
    p->right = right;

    return p;
}

void insert(Node *heap[], int *size, Node *x) {
    int i = (*size)++;

    while (i > 0) {
        int p = (i - 1) / 2;

        if (heap[p]->freq < x->freq ||
            (heap[p]->freq == x->freq &&
             heap[p]->minSymbol <= x->minSymbol))
            break;

        heap[i] = heap[p];
        i = p;
    }

    heap[i] = x;
}

Node *removeMin(Node *heap[], int *size) {
    Node *result = heap[0];
    Node *last = heap[--(*size)];

    if (*size == 0)
        return result;

    int i = 0;

    while (2 * i + 1 < *size) {
        int c = 2 * i + 1;

        if (c + 1 < *size &&
            (heap[c + 1]->freq < heap[c]->freq ||
             (heap[c + 1]->freq == heap[c]->freq &&
              heap[c + 1]->minSymbol < heap[c]->minSymbol)))
            c++;

        if (last->freq < heap[c]->freq ||
            (last->freq == heap[c]->freq &&
             last->minSymbol <= heap[c]->minSymbol))
            break;

        heap[i] = heap[c];
        i = c;
    }

    heap[i] = last;
    return result;
}

void getLengths(Node *root, int depth, int lengths[]) {
    if (!root)
        return;

    if (root->symbol >= 0) {
        lengths[root->symbol] = depth ? depth : 1;
        return;
    }

    getLengths(root->left, depth + 1, lengths);
    getLengths(root->right, depth + 1, lengths);
}

int compareSymbols(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;

    extern int lengthsForSort[];

    if (lengthsForSort[x] != lengthsForSort[y])
        return lengthsForSort[x] - lengthsForSort[y];

    return x - y;
}

int lengthsForSort[MAX];

void printCode(unsigned long long code, int len) {
    int i;

    for (i = len - 1; i >= 0; i--)
        printf("%d", (int)((code >> i) & 1ULL));
}

int main() {
    int n, i, size = 0;
    int freq[MAX], lengths[MAX] = {0};
    int symbols[MAX];
    Node *heap[MAX];

    printf("Enter number of symbols (1-256): ");
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Invalid number of symbols.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("Enter frequency for symbol %c: ", i + 1);
        if (scanf("%d", &freq[i]) != 1 || freq[i] <= 0) {
            printf("Frequencies must be positive.\n");
            return 1;
        }

        heap[size] = newNode(freq[i], i, i, NULL, NULL);
        size++;
    }

    while (size > 1) {
        Node *a = removeMin(heap, &size);
        Node *b = removeMin(heap, &size);

        Node *p = newNode(a->freq + b->freq, -1,
                          a->minSymbol < b->minSymbol ?
                          a->minSymbol : b->minSymbol,
                          a, b);

        insert(heap, &size, p);
    }

    getLengths(heap[0], 0, lengths);

    for (i = 0; i < n; i++) {
        symbols[i] = i;
        lengthsForSort[i] = lengths[i];
    }

    qsort(symbols, n, sizeof(int), compareSymbols);

    unsigned long long code = 0;
    int previousLength = lengths[symbols[0]];

    printf("\nCanonical Huffman Codes:\n");

    for (i = 0; i < n; i++) {
        int s = symbols[i];
        int len = lengths[s];

        if (i > 0) {
            code++;
            code <<= (len - previousLength);
        }

        printf("Symbol %c: ", 'A' + s);

        if (len > 64) {
            printf("Code too long for 64-bit display\n");
        } else {
            printCode(code, len);
            printf("\n");
        }

        previousLength = len;
    }

    return 0;
}