#include <stdio.h>
typedef struct {
    double value;
    double weight;
    double decay;
    double fraction;
} Item;

int main() {
    Item a[100];
    int n, i, j;
    double W, time = 0, total = 0;

    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter capacity: ");
    scanf("%lf", &W);

    for (i = 0; i < n; i++) {
        printf("Enter value, weight and decay rate: ");
        scanf("%lf %lf %lf",&a[i].value, &a[i].weight, &a[i].decay);
        a[i].fraction = 0;
    }

    for (i = 0; i < n; i++) {
        if (a[i].weight <= 0 || a[i].decay < 0) {
            printf("Invalid input.\n");
            return 1;
        }
    }

    while (W > 1e-9) {
        int best = -1;
        double bestDensity = 0;

        for (i = 0; i < n; i++) {
            if (a[i].fraction < 1.0 - 1e-9) {
                double density =
                    a[i].value / a[i].weight - a[i].decay * time;

                if (best == -1 || density > bestDensity) {
                    bestDensity = density;
                    best = i;
                }
            }
        }

        if (best == -1 || bestDensity <= 0)
            break;

        double remaining =
            a[best].weight * (1.0 - a[best].fraction);

        double take = remaining < W ? remaining : W;

        a[best].fraction += take / a[best].weight;

        total += take * bestDensity;
        W -= take;
        time++;
    }

    printf("Selected fractions:\n");

    for (i = 0; i < n; i++)
        printf("Item %d: %.2f\n", i + 1, a[i].fraction);

    printf("Accumulated value: %.2f\n", total);

    return 0;
}